/*
 * Copyright (c) 2009-2012 jMonkeyEngine
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * * Neither the name of 'jMonkeyEngine' nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Author: Normen Hansen, CJ Hare
 */
#include "com_jme3_bullet_util_DebugShapeFactory.h"
#include "jmeBulletUtil.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"

class DebugCallback : public btTriangleCallback, public btInternalTriangleIndexCallback {
public:
    JNIEnv *env;
    jobject callback;

    DebugCallback(JNIEnv *env, jobject object) {
        this->env = env;
        this->callback = object;
    }

    virtual void internalProcessTriangleIndex(btVector3* triangle, int partId, int triangleIndex) {
        processTriangle(triangle, partId, triangleIndex);
    }

    virtual void processTriangle(btVector3* triangle, int partId, int triangleIndex) {
        btVector3 vertexA, vertexB, vertexC;
        vertexA = triangle[0];
        vertexB = triangle[1];
        vertexC = triangle[2];
        env->CallVoidMethod(callback, jmeClasses::DebugMeshCallback_addVector, vertexA.getX(), vertexA.getY(), vertexA.getZ(), partId, triangleIndex);
        if (env->ExceptionCheck()) {
            env->Throw(env->ExceptionOccurred());
            return;
        }
        env->CallVoidMethod(callback, jmeClasses::DebugMeshCallback_addVector, vertexB.getX(), vertexB.getY(), vertexB.getZ(), partId, triangleIndex);
        if (env->ExceptionCheck()) {
            env->Throw(env->ExceptionOccurred());
            return;
        }
        env->CallVoidMethod(callback, jmeClasses::DebugMeshCallback_addVector, vertexC.getX(), vertexC.getY(), vertexC.getZ(), partId, triangleIndex);
        if (env->ExceptionCheck()) {
            env->Throw(env->ExceptionOccurred());
            return;
        }
    }
};

extern "C" {

    void getVertices(JNIEnv *env, jlong shapeId, jint resolution,
            jobject callback) {
        btCollisionShape *pShape
                = reinterpret_cast<btCollisionShape *> (shapeId);
        if (pShape->isConcave()) {
            btConcaveShape *pConcave
                    = reinterpret_cast<btConcaveShape *> (shapeId);

            DebugCallback *pCallback = new DebugCallback(env, callback);
            btVector3 min = btVector3(-1e30, -1e30, -1e30);
            btVector3 max = btVector3(1e30, 1e30, 1e30);
            pConcave->processAllTriangles(pCallback, min, max);
            delete pCallback;

        } else if (pShape->isConvex()) {
            btConvexShape *pConvex
                    = reinterpret_cast<btConvexShape *> (shapeId);

            // Create a hull approximation.
            btShapeHull *pHull = new btShapeHull(pConvex);
            float margin = pConvex->getMargin();
            pHull->buildHull(margin, resolution);

            int numberOfTriangles = pHull->numTriangles();
            const unsigned int *pHullIndices = pHull->getIndexPointer();
            const btVector3 *pHullVertices = pHull->getVertexPointer();
            btVector3 vertexA, vertexB, vertexC;
            int index = 0;

            for (int i = 0; i < numberOfTriangles; i++) {
                // Copy the triangle's vertices from the hull.
                vertexA = pHullVertices[pHullIndices[index++]];
                vertexB = pHullVertices[pHullIndices[index++]];
                vertexC = pHullVertices[pHullIndices[index++]];

                // Add the vertices to the callback object.
                env->CallVoidMethod(callback,
                        jmeClasses::DebugMeshCallback_addVector, vertexA.getX(),
                        vertexA.getY(), vertexA.getZ());
                if (env->ExceptionCheck()) {
                    env->Throw(env->ExceptionOccurred());
                    return;
                }
                env->CallVoidMethod(callback,
                        jmeClasses::DebugMeshCallback_addVector, vertexB.getX(),
                        vertexB.getY(), vertexB.getZ());
                if (env->ExceptionCheck()) {
                    env->Throw(env->ExceptionOccurred());
                    return;
                }
                env->CallVoidMethod(callback,
                        jmeClasses::DebugMeshCallback_addVector, vertexC.getX(),
                        vertexC.getY(), vertexC.getZ());
                if (env->ExceptionCheck()) {
                    env->Throw(env->ExceptionOccurred());
                    return;
                }
            }
            delete pHull;
        }
    }

    /*
     * Class:     com_jme3_bullet_util_DebugShapeFactory
     * Method:    getVertices2
     * Signature: (JILcom/jme3/bullet/util/DebugMeshCallback;)V
     */
    JNIEXPORT void JNICALL Java_com_jme3_bullet_util_DebugShapeFactory_getVertices2
    (JNIEnv *env, jclass clazz, jlong shapeId, jint resolution,
            jobject callback) {
        getVertices(env, shapeId, resolution, callback);
    }
}
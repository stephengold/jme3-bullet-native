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
 * Author: Normen Hansen
 */

#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include "com_jme3_bullet_objects_PhysicsGhostObject.h"
#include "BulletCollision/BroadphaseCollision/btOverlappingPairCache.h"
#include "jmeBulletUtil.h"
#include "jmePhysicsSpace.h"

#ifdef __cplusplus
extern "C" {
#endif

    class jmeGhostOverlapCallback : public btOverlapCallback {
        JNIEnv* m_env;
        jobject m_object;
        btCollisionObject *m_ghost;
    public:

        jmeGhostOverlapCallback(JNIEnv *env, jobject object, btCollisionObject *ghost)
        : m_env(env),
        m_object(object),
        m_ghost(ghost) {
        }

        virtual ~jmeGhostOverlapCallback() {
        }

        virtual bool processOverlap(btBroadphasePair& pair) {
            btCollisionObject *other;
            if (pair.m_pProxy1->m_clientObject == m_ghost) {
                other = (btCollisionObject *) pair.m_pProxy0->m_clientObject;
            } else {
                other = (btCollisionObject *) pair.m_pProxy1->m_clientObject;
            }
            jmeUserPointer *up1 = (jmeUserPointer*) other -> getUserPointer();
            jobject javaCollisionObject1
                    = m_env->NewLocalRef(up1->javaCollisionObject);
            m_env->CallVoidMethod(m_object,
                    jmeClasses::PhysicsGhostObject_addOverlappingObject,
                    javaCollisionObject1);
            m_env->DeleteLocalRef(javaCollisionObject1);
            if (m_env->ExceptionCheck()) {
                m_env->Throw(m_env->ExceptionOccurred());
                return false;
            }

            return false;
        }
    };

    /*
     * Class:     com_jme3_bullet_objects_PhysicsGhostObject
     * Method:    createGhostObject
     * Signature: ()J
     */
    JNIEXPORT jlong JNICALL Java_com_jme3_bullet_objects_PhysicsGhostObject_createGhostObject
    (JNIEnv * env, jobject object) {
        jmeClasses::initJavaClasses(env);

        btPairCachingGhostObject* ghost = new btPairCachingGhostObject();

        return reinterpret_cast<jlong> (ghost);
    }

    /*
     * Class:     com_jme3_bullet_objects_PhysicsGhostObject
     * Method:    getOverlappingCount
     * Signature: (J)I
     */
    JNIEXPORT jint JNICALL Java_com_jme3_bullet_objects_PhysicsGhostObject_getOverlappingCount
    (JNIEnv *env, jobject object, jlong objectId) {
        btPairCachingGhostObject* ghost
                = reinterpret_cast<btPairCachingGhostObject*> (objectId);
        NULL_CHECK(ghost, "The btPairCachingGhostObject does not exist.", 0)
        btAssert(ghost->getInternalType() & btCollisionObject::CO_GHOST_OBJECT);

        return ghost->getNumOverlappingObjects();
    }

    /*
     * Class:     com_jme3_bullet_objects_PhysicsGhostObject
     * Method:    getOverlappingObjects
     * Signature: (J)V
     */
    JNIEXPORT void JNICALL Java_com_jme3_bullet_objects_PhysicsGhostObject_getOverlappingObjects
    (JNIEnv *env, jobject object, jlong objectId) {
        btPairCachingGhostObject* ghost
                = reinterpret_cast<btPairCachingGhostObject*> (objectId);
        NULL_CHECK(ghost, "The btPairCachingGhostObject does not exist.",)
        btAssert(ghost->getInternalType() & btCollisionObject::CO_GHOST_OBJECT);

        btHashedOverlappingPairCache * pc = ghost->getOverlappingPairCache();
        jmeGhostOverlapCallback cb(env, object, ghost);
        pc -> processAllOverlappingPairs(&cb, NULL);
    }

    /*
     * Class:     com_jme3_bullet_objects_PhysicsGhostObject
     * Method:    setGhostFlags
     * Signature: (J)V
     */
    JNIEXPORT void JNICALL Java_com_jme3_bullet_objects_PhysicsGhostObject_setGhostFlags
    (JNIEnv *env, jobject object, jlong objectId) {
        btPairCachingGhostObject* ghost
                = reinterpret_cast<btPairCachingGhostObject*> (objectId);
        NULL_CHECK(ghost, "The btPairCachingGhostObject does not exist.",)
        btAssert(ghost->getInternalType() & btCollisionObject::CO_GHOST_OBJECT);

        ghost->setCollisionFlags(ghost->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
    }

    /*
     * Class:     com_jme3_bullet_objects_PhysicsGhostObject
     * Method:    setPhysicsLocation
     * Signature: (JLcom/jme3/math/Vector3f;)V
     */
    JNIEXPORT void JNICALL Java_com_jme3_bullet_objects_PhysicsGhostObject_setPhysicsLocation
    (JNIEnv *env, jobject object, jlong objectId, jobject value) {
        btPairCachingGhostObject* ghost
                = reinterpret_cast<btPairCachingGhostObject*> (objectId);
        NULL_CHECK(ghost, "The btPairCachingGhostObject does not exist.",)
        btAssert(ghost->getInternalType() & btCollisionObject::CO_GHOST_OBJECT);

        NULL_CHECK(value, "The vector does not exist.",)

        jmeBulletUtil::convert(env, value,
                &ghost->getWorldTransform().getOrigin());
    }

    /*
     * Class:     com_jme3_bullet_objects_PhysicsGhostObject
     * Method:    setPhysicsRotation
     * Signature: (JLcom/jme3/math/Matrix3f;)V
     */
    JNIEXPORT void JNICALL Java_com_jme3_bullet_objects_PhysicsGhostObject_setPhysicsRotation__JLcom_jme3_math_Matrix3f_2
    (JNIEnv *env, jobject object, jlong objectId, jobject value) {
        btPairCachingGhostObject* ghost
                = reinterpret_cast<btPairCachingGhostObject*> (objectId);
        NULL_CHECK(ghost, "The btPairCachingGhostObject does not exist.",)
        btAssert(ghost->getInternalType() & btCollisionObject::CO_GHOST_OBJECT);

        NULL_CHECK(value, "The matrix does not exist.",)

        jmeBulletUtil::convert(env, value, &ghost->getWorldTransform().getBasis());
    }

    /*
     * Class:     com_jme3_bullet_objects_PhysicsGhostObject
     * Method:    setPhysicsRotation
     * Signature: (JLcom/jme3/math/Quaternion;)V
     */
    JNIEXPORT void JNICALL Java_com_jme3_bullet_objects_PhysicsGhostObject_setPhysicsRotation__JLcom_jme3_math_Quaternion_2
    (JNIEnv *env, jobject object, jlong objectId, jobject value) {
        btPairCachingGhostObject* ghost
                = reinterpret_cast<btPairCachingGhostObject*> (objectId);
        NULL_CHECK(ghost, "The btPairCachingGhostObject does not exist.",)
        btAssert(ghost->getInternalType() & btCollisionObject::CO_GHOST_OBJECT);

        NULL_CHECK(value, "The quaternion does not exist.",)

        jmeBulletUtil::convertQuat(env, value,
                &ghost->getWorldTransform().getBasis());
    }

#ifdef __cplusplus
}
#endif

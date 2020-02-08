/*
 * Copyright (c) 2020 jMonkeyEngine
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
 * Author: Stephen Gold
 */
#include "vhacd_VHACDHull.h"
#include "jmeBulletUtil.h"
#include "VHACD.h"
extern "C" {
    using namespace VHACD;

    /*
     * Class:     vhacd_VHACDHull
     * Method:    getIndices
     * Signature: (JLjava/nio/IntBuffer;)V
     */
    JNIEXPORT void JNICALL Java_vhacd_VHACDHull_getIndices
    (JNIEnv *env, jclass clas, jlong hullId, jobject storeBuffer) {
        const IVHACD::ConvexHull * const pHull
                = reinterpret_cast<IVHACD::ConvexHull *> (hullId);
        NULL_CHECK(pHull, "The hull does not exist.",)

        NULL_CHECK(storeBuffer, "The indices buffer does not exist.",);
        jint * const pIndices
                = (jint *) env->GetDirectBufferAddress(storeBuffer);
        NULL_CHECK(pIndices, "The indices buffer is not direct.",);

        const jlong capacity = env->GetDirectBufferCapacity(storeBuffer);
        const uint32_t numInts = 3 * pHull->m_nTriangles;
        for (uint32_t i = 0; i < numInts && i < capacity; ++i) {
            pIndices[i] = pHull->m_triangles[i];
        }
    }

    /*
     * Class:     vhacd_VHACDHull
     * Method:    getNumFloats
     * Signature: (J)I
     */
    JNIEXPORT jint JNICALL Java_vhacd_VHACDHull_getNumFloats
    (JNIEnv *env, jclass clas, jlong hullId) {
        const IVHACD::ConvexHull * const pHull
                = reinterpret_cast<IVHACD::ConvexHull *> (hullId);
        NULL_CHECK(pHull, "The hull does not exist.", 0);

        uint32_t numFloats = 3 * pHull->m_nPoints;

        return (jint) numFloats;
    }

    /*
     * Class:     vhacd_VHACDHull
     * Method:    getNumInts
     * Signature: (J)I
     */
    JNIEXPORT jint JNICALL Java_vhacd_VHACDHull_getNumInts
    (JNIEnv *env, jclass clas, jlong hullId) {
        const IVHACD::ConvexHull * const pHull
                = reinterpret_cast<IVHACD::ConvexHull *> (hullId);
        NULL_CHECK(pHull, "The hull does not exist.", 0);

        uint32_t numInts = 3 * pHull->m_nTriangles;

        return (jint) numInts;
    }

    /*
     * Class:     vhacd_VHACDHull
     * Method:    getPositions
     * Signature: (JLjava/nio/FloatBuffer;)V
     */
    JNIEXPORT void JNICALL Java_vhacd_VHACDHull_getPositions
    (JNIEnv *env, jclass clas, jlong hullId, jobject storeBuffer) {
        const IVHACD::ConvexHull * const pHull
                = reinterpret_cast<IVHACD::ConvexHull *> (hullId);
        NULL_CHECK(pHull, "The hull does not exist.",)

        NULL_CHECK(storeBuffer, "The positions buffer does not exist.",);
        jfloat * const pPositions
                = (jfloat *) env->GetDirectBufferAddress(storeBuffer);
        NULL_CHECK(pPositions, "The positions buffer is not direct.",);

        const jlong capacity = env->GetDirectBufferCapacity(storeBuffer);
        const uint32_t numFloats = 3 * pHull->m_nPoints;
        for (uint32_t i = 0; i < numFloats && i < capacity; ++i) {
            pPositions[i] = pHull->m_points[i];
        }
    }
}
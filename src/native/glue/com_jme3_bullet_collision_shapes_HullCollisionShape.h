/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_jme3_bullet_collision_shapes_HullCollisionShape */

#ifndef _Included_com_jme3_bullet_collision_shapes_HullCollisionShape
#define _Included_com_jme3_bullet_collision_shapes_HullCollisionShape
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_jme3_bullet_collision_shapes_HullCollisionShape
 * Method:    countHullVertices
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_jme3_bullet_collision_shapes_HullCollisionShape_countHullVertices
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_jme3_bullet_collision_shapes_HullCollisionShape
 * Method:    createShapeB
 * Signature: (Ljava/nio/ByteBuffer;I)J
 */
JNIEXPORT jlong JNICALL Java_com_jme3_bullet_collision_shapes_HullCollisionShape_createShapeB
  (JNIEnv *, jobject, jobject, jint);

/*
 * Class:     com_jme3_bullet_collision_shapes_HullCollisionShape
 * Method:    getHullVertices
 * Signature: (JLjava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_com_jme3_bullet_collision_shapes_HullCollisionShape_getHullVertices
  (JNIEnv *, jobject, jlong, jobject);

#ifdef __cplusplus
}
#endif
#endif

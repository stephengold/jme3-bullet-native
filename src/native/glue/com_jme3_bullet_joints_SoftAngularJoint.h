/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_jme3_bullet_joints_SoftAngularJoint */

#ifndef _Included_com_jme3_bullet_joints_SoftAngularJoint
#define _Included_com_jme3_bullet_joints_SoftAngularJoint
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_jme3_bullet_joints_SoftAngularJoint
 * Method:    createJointSoftRigid
 * Signature: (JJLcom/jme3/math/Vector3f;Lcom/jme3/math/Vector3f;FFFLcom/jme3/math/Vector3f;)J
 */
JNIEXPORT jlong JNICALL Java_com_jme3_bullet_joints_SoftAngularJoint_createJointSoftRigid
  (JNIEnv *, jobject, jlong, jlong, jobject, jobject, jfloat, jfloat, jfloat, jobject);

/*
 * Class:     com_jme3_bullet_joints_SoftAngularJoint
 * Method:    createJointSoftSoft
 * Signature: (JJLcom/jme3/math/Vector3f;Lcom/jme3/math/Vector3f;FFFLcom/jme3/math/Vector3f;)J
 */
JNIEXPORT jlong JNICALL Java_com_jme3_bullet_joints_SoftAngularJoint_createJointSoftSoft
  (JNIEnv *, jobject, jlong, jlong, jobject, jobject, jfloat, jfloat, jfloat, jobject);

/*
 * Class:     com_jme3_bullet_joints_SoftAngularJoint
 * Method:    setAxis
 * Signature: (JLcom/jme3/math/Vector3f;)V
 */
JNIEXPORT void JNICALL Java_com_jme3_bullet_joints_SoftAngularJoint_setAxis
  (JNIEnv *, jobject, jlong, jobject);

#ifdef __cplusplus
}
#endif
#endif

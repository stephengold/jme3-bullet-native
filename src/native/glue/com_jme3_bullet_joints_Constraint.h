/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_jme3_bullet_joints_Constraint */

#ifndef _Included_com_jme3_bullet_joints_Constraint
#define _Included_com_jme3_bullet_joints_Constraint
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_jme3_bullet_joints_Constraint
 * Method:    finalizeNative
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_jme3_bullet_joints_Constraint_finalizeNative
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_jme3_bullet_joints_Constraint
 * Method:    getConstraintType
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_jme3_bullet_joints_Constraint_getConstraintType
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_jme3_bullet_joints_Constraint
 * Method:    enableFeedback
 * Signature: (JZ)V
 */
JNIEXPORT void JNICALL Java_com_jme3_bullet_joints_Constraint_enableFeedback
  (JNIEnv *, jobject, jlong, jboolean);

/*
 * Class:     com_jme3_bullet_joints_Constraint
 * Method:    getAppliedImpulse
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_com_jme3_bullet_joints_Constraint_getAppliedImpulse
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_jme3_bullet_joints_Constraint
 * Method:    getBreakingImpulseThreshold
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_com_jme3_bullet_joints_Constraint_getBreakingImpulseThreshold
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_jme3_bullet_joints_Constraint
 * Method:    isEnabled
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_jme3_bullet_joints_Constraint_isEnabled
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_jme3_bullet_joints_Constraint
 * Method:    needsFeedback
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_jme3_bullet_joints_Constraint_needsFeedback
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_jme3_bullet_joints_Constraint
 * Method:    setBreakingImpulseThreshold
 * Signature: (JF)V
 */
JNIEXPORT void JNICALL Java_com_jme3_bullet_joints_Constraint_setBreakingImpulseThreshold
  (JNIEnv *, jobject, jlong, jfloat);

/*
 * Class:     com_jme3_bullet_joints_Constraint
 * Method:    setEnabled
 * Signature: (JZ)V
 */
JNIEXPORT void JNICALL Java_com_jme3_bullet_joints_Constraint_setEnabled
  (JNIEnv *, jobject, jlong, jboolean);

#ifdef __cplusplus
}
#endif
#endif

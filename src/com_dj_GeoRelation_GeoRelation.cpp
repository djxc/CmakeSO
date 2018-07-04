#include "com_dj_GeoRelation_GeoRelation.h"
#include <iostream>
#include <cstring>
#include "point.h"
#include "PointOper.h"
#include <algorithm>


using namespace std;

JNIEXPORT jint JNICALL Java_com_dj_GeoRelation_GeoRelation_isPointOnLine
  (JNIEnv *env, jclass, jobject point, jobject line)
{	
	jclass jpoint = env -> GetObjectClass(point);
	jclass jline = env -> GetObjectClass(line);

	if(jpoint == NULL && jline == NULL)
	{
		return 0;
	}
	jmethodID getXMID = env -> GetMethodID(jpoint, "getX", "()D");
	jmethodID getYMID = env -> GetMethodID(jpoint, "getY", "()D");
	jmethodID getStart = env -> GetMethodID(jline, "getStart_p", "()Lcom/dj/Geometry/Point;");
	jmethodID getEnd = env -> GetMethodID(jline, "getEnd_p", "()Lcom/dj/Geometry/Point;");

//	jfieldID startP = env -> GetFieldID(jline, "start_p");
	if(getXMID == NULL && getStart == NULL && getEnd == NULL){
		return 0;
	}
	jdouble px = (jdouble)env -> CallDoubleMethod(point, getXMID, NULL);
	jdouble py = (jdouble)env -> CallDoubleMethod(point, getYMID, NULL);

	jobject startP = env -> CallObjectMethod(line, getStart, NULL);
	jobject endP = env -> CallObjectMethod(line, getEnd, NULL);

	jdouble SPx =  (jdouble)env -> CallDoubleMethod(startP, getXMID, NULL);
	jdouble SPy =  (jdouble)env -> CallDoubleMethod(startP, getYMID, NULL);
	jdouble EPx =  (jdouble)env -> CallDoubleMethod(endP, getXMID, NULL);
	jdouble EPy =  (jdouble)env -> CallDoubleMethod(endP, getYMID, NULL);
	
	Point p1(px, py), s(SPx, SPy), e(EPx, EPy);
	PointOper po1(p1, s), po2(e, s);
	
	Point op1 = po1.pointMinus();
	Point op2 = po2.pointMinus();
	PointOper po3(op1, op2);
	
	double pp = po3.pointMult();
	if(pp == 0)
	{
		px += 5;
		if((min(SPx, EPx) <= px)
			&& (max(SPx, EPx) >= px)
			&& (min(SPy, EPy) <= py)
			&& (max(SPy, EPy) >= py)){
			return 1;
		}  
		else{
			return 2;
																																		}
	}else{
		return 0;
	}

//	return (jint)pp;
}

JNIEXPORT jdoubleArray JNICALL Java_com_dj_GeoRelation_GeoRelation_LineLine
  (JNIEnv *env, jclass, jdoubleArray point)
{
	 jint i, sum = 0;
     jdouble *c_array;
     jsize arr_len;
	 //获取数组的指针
	 c_array = env->GetDoubleArrayElements(point, 0);
     if (c_array == NULL) {
         return NULL;   // JVM复制原始数据到缓冲区失败
     }
	 //获取数组的大小
     arr_len = env->GetArrayLength(point);
     jdoubleArray jarr = env->NewDoubleArray(arr_len);
	 for (i = 0; i < arr_len; i++) {
		 c_array[i] +=  2;
	 }
	 env -> ReleaseDoubleArrayElements(jarr, c_array, 0);
	return jarr;
	
}

JNIEXPORT jstring JNICALL Java_com_dj_GeoRelation_GeoRelation_getStr
  (JNIEnv *env, jclass, jstring jstr)
{
	const char *str = env -> GetStringUTFChars(jstr, 0);
	char c[20] = "dj";
	strcat(c, str);
	env -> ReleaseStringUTFChars(jstr, str);
	return env -> NewStringUTF(c);
}

  /*
   * Class:     com_dj_GeoRelation_GeoRelation
   * Method:    getObject
   * Signature: (Lcom/dj/JNIDemo/Person;)Lcom/dj/JNIDemo/Person;
   */
 JNIEXPORT jobject JNICALL Java_com_dj_GeoRelation_GeoRelation_getObject
   (JNIEnv *env, jclass, jobject person)
{
	jclass jcls = env -> GetObjectClass(person);
	if(jcls == NULL)
	{
		return env -> NewStringUTF("not find class");
	}
	jmethodID constrocMID = env -> GetMethodID(jcls, "<init>", "(ILjava/lang/String;)V");
	if(constrocMID == NULL){
		return env -> NewStringUTF("not find constroc method");
	}

	jstring str = env -> NewStringUTF("djxc");
	jobject new_obj = env -> NewObject(jcls, constrocMID, 27, str);
	return new_obj;

}

	/*
	 * Class:     com_dj_GeoRelation_GeoRelation
	 * Method:    getPersonList
	 * Signature: (Ljava/util/ArrayList;)Ljava/util/ArrayList;
	 */
JNIEXPORT jobject JNICALL Java_com_dj_GeoRelation_GeoRelation_getPersonList
  (JNIEnv *env, jclass, jobject jlist)
{
	jclass jcls = env -> GetObjectClass(jlist);
	if(jcls == NULL)
	{
		return env -> NewStringUTF("not find class");
	}
	jmethodID constrocMID = env -> GetMethodID(jcls, "<init>", "()V");
	if(constrocMID == NULL){
		return env -> NewStringUTF("not find constroc method");
	}
	//创建一个Arraylist集合对象
    jobject list_obj = env->NewObject(jcls,constrocMID);
    //获取list的add方法id
    jmethodID list_add  = env->GetMethodID(jcls,"add","(Ljava/lang/Object;)Z");

    jclass jpersonCls = env->FindClass("com/dj/JNIDemo/Person");

    jmethodID jpersonConstrocMID = env->GetMethodID(jpersonCls,"<init>","(ILjava/lang/String;)V");

    for(int i = 0 ; i < 3 ; i++)
     {
         jstring str = env->NewStringUTF("Native");
         //通过调用该对象的构造函数来new 一个 person实例
         jobject per_obj = env->NewObject(jpersonCls , jpersonConstrocMID , 20+i ,str);  //构造一个person对象
        //执行Arraylist类实例的add方法，添加一个person对象
        env->CallBooleanMethod(list_obj ,list_add, per_obj);
     }
	 return list_obj;
}

//获取java传递来的对象,并获取对象的方法,并调用方法
JNIEXPORT jint JNICALL Java_com_dj_GeoRelation_GeoRelation_passObject
  (JNIEnv *env, jclass, jobject point)
{
	jclass jcls = env -> GetObjectClass(point);
	if(jcls == NULL)
	{
		return -1;
	}
	jmethodID getXMID = env -> GetMethodID(jcls, "getX", "()D");
	if(getXMID == NULL){
		return -1;
	}
	jdouble x = (jdouble)env -> CallDoubleMethod(point, getXMID, NULL);
	return (jint)x;

}

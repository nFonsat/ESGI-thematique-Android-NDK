#include <jni.h>
#include <string>
#include <stdlib.h>

extern "C"
{
int cmpfunc (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

JNIEXPORT jintArray JNICALL
Java_fr_nicolasfonsat_oodsphere_MainActivity_solution(JNIEnv *env, jobject, jint nbParticipant, jint gift, jintArray budgets) {
    jint * budgetAr = env->GetIntArrayElements(budgets, NULL);
    jintArray result = env->NewIntArray(nbParticipant);
    jint * resultAr = env->GetIntArrayElements(result, NULL);

    qsort(budgetAr, (size_t) nbParticipant, sizeof(int), cmpfunc);

    int sumMax = 0;
    for (int i = 0; i < nbParticipant; ++i) {
        sumMax += budgetAr[i];
    }

    if (sumMax < gift) {
        return result;
    }

    int nbWithoutPay = nbParticipant;
    int due = gift;
    for(int i = 0; i < nbParticipant; ++i){

        if(budgetAr[i] < due/nbWithoutPay){
            jint toPay = budgetAr[i];
            resultAr[i] = toPay;
            due -= toPay;
        } else {
            if ( nbWithoutPay == 1) {
                jint toPay = due;
                resultAr[i] = toPay;
                due -= toPay;
            }
            else {
                jint toPay = due/nbWithoutPay - (due % nbWithoutPay);
                resultAr[i] = toPay;
                due -= toPay;
            }
        }
        nbWithoutPay--;
    }

    env->ReleaseIntArrayElements(result, resultAr, NULL);
    return result;
}
}
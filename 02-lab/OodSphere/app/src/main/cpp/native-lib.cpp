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
Java_fr_nicolasfonsat_oodsphere_MainActivity_solution(
        JNIEnv *env, jobject,
        jint nbParticipant, // Le nombre de participant
        jint gift, // Le prix du cadeaux
        jintArray budgets /*// Un tableau des budget de chaque participant */) {

    jint * budgetAr = env->GetIntArrayElements(budgets, NULL); //jintArray -> jint *
    jintArray result = env->NewIntArray(nbParticipant);
    jint * resultAr = env->GetIntArrayElements(result, NULL); //jintArray -> jint *

    // On trie le tableau par le plus petit budget
    qsort(budgetAr, (size_t) nbParticipant, sizeof(int), cmpfunc);

    //Vérification que le budget max soit suffisant
    int sumMax = 0;
    for (int i = 0; i < nbParticipant; ++i) {
        sumMax += budgetAr[i];
    }

    if (sumMax < gift) {
        return result;
    }


    int nbWithoutPay = nbParticipant; // Participant qui n'ont pas encore payer
    int due = gift; // Reste à payer
    for(int i = 0; i < nbParticipant; ++i){

        // Si le budget du particpant est inférieur au budget équitable par participant
        // alors on prend tout sont budget
        // sinon on prend une somme équitable avec le reste des participants
        // Cas particulier: S'il reste un participant alors on prend la somme qui manque..
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

    env->ReleaseIntArrayElements(result, resultAr, NULL);//jint * -> jintArray
    return result;
}
}
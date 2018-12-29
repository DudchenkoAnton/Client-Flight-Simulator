//
// Created by anton on 12/27/18.
//

#include "MutexClass.h"


MutexClass* MutexClass :: instance = NULL;

/**
 * Method checks if already created instance of MutexClass. If it is, it returns
 * pointer to this class. Else, it creates instance of class, and saves it as member.
 */
MutexClass* MutexClass ::getInstance() {

    if(instance == 0) {

        instance = new MutexClass();
    }

    return instance;
}

/**
 * Method returns pointer to mutex.
 * @return - pointer of mutex.
 */
pthread_mutex_t* MutexClass :: getMutex() {

    return &mutex1;
}
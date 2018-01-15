/*
 * General.hpp
 *
 *  Created on: 11 Oct 2017
 *      Author: SengMing
 */

#ifndef GENERAL_HPP_
#define GENERAL_HPP_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cExec cExec;
cExec* newExec();
void deleteExec(cExec* exec);
void runExec(cExec* exec);

#ifdef __cplusplus
}
#endif



#endif /* GENERAL_HPP_ */

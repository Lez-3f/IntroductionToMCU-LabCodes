/*
 * Qinghuaci.h
 *
 *  Created on: 2021Äê8ÔÂ26ÈÕ
 *      Author: ZEL
 */

#ifndef QINGHUACI_H_
#define QINGHUACI_H_

const unsigned int QHC[92] = {
                            non, sol_m, sol_m, mi_m,
                            re_m, mi_m, la_l,
                            re_m, mi_m, sol_m, mi_m,
                            re_m,
                            non, sol_m, sol_m, mi_m,
                            re_m, mi_m, sol_l,
                            re_m, mi_m, sol_m, re_m,
                            do_m,
                            non, do_m, re_m, mi_m,
                            sol_m, la_m, sol_m, fa_m,
                            sol_m, mi_m, mi_m, re_m,
                            re_m,
                            non, do_m, re_m, do_m,
                            do_m, re_m, do_m, re_m,
                            re_m, mi_m, sol_m,
                            mi_m, mi_m,
                            //
                            non, sol_m, sol_m, mi_m,
                            re_m, mi_m, la_l,
                            re_m, mi_m, sol_m, mi_m,
                            re_m,
                            non, sol_m, sol_m, mi_m,
                            re_m, mi_m, sol_l,
                            re_m, mi_m, sol_m, re_m,
                            do_m,
                            non, do_m, re_m, mi_m,
                            sol_m, la_m, sol_m, fa_m,
                            sol_m, mi_m, mi_m, re_m,
                            re_m, sol_l,
                            mi_m, re_m, re_m,
                            do_m
};

const unsigned int Beats_QHC[92] = {
                                  beat_1, beat_1, beat_1, beat_1,
                                  beat_1, beat_1, beat_2,
                                  beat_1, beat_1, beat_1, beat_1,
                                  beat_4,
                                  beat_1, beat_1, beat_1, beat_1,
                                  beat_1, beat_1, beat_2,
                                  beat_1, beat_1, beat_1, beat_1,
                                  beat_3, beat_1,
                                  beat_1, beat_1, beat_1, beat_1,
                                  beat_1, beat_1, beat_1, beat_1,
                                  beat_1, beat_1, beat_1, beat_1,
                                  beat_4,
                                  beat_1, beat_1, beat_1, beat_1,
                                  beat_1, beat_1, beat_1, beat_1,
                                  beat_1, beat_2, beat_1,
                                  beat_4,
                                  //
                                  beat_1, beat_1, beat_1, beat_1,
                                  beat_1, beat_1, beat_2,
                                  beat_1, beat_1, beat_1, beat_1,
                                  beat_4,
                                  beat_1, beat_1, beat_1, beat_1,
                                  beat_1, beat_1, beat_2,
                                  beat_1, beat_1, beat_1, beat_1,
                                  beat_4,
                                  beat_1, beat_1, beat_1, beat_1,
                                  beat_1, beat_1, beat_1, beat_1,
                                  beat_1, beat_1, beat_1, beat_1,
                                  beat_3, beat_1,
                                  beat_2, beat_1, beat_1,
                                  beat_4
};

const int note_num_QHC = 92;

#endif /* QINGHUACI_H_ */

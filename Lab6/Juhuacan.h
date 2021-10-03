/*
 * Juhuacan.h
 *
 *  Created on: 2021Äê8ÔÂ27ÈÕ
 *      Author: ZEL
 */

#ifndef JUHUACAN_H_
#define JUHUACAN_H_

const unsigned int JHT[24] = {
                            do_m, re_m,
                            mi_m,
                            mi_m, sol_m,
                            la_m,
                            la_m, mi_h,
                            re_h, do_h,
                            do_h, la_m,
                            sol_m,
                            la_m, sol_m,
                            mi_m, re_m,
                            do_m,
                            la_l, do_m,
                            re_m,
                            re_m, do_m,
                            re_m
};
const unsigned int Beats_JHT[24] = {
                                    beat_2, beat_2,
                                    beat_4,
                                    beat_2, beat_2,
                                    beat_4,
                                    beat_2, beat_2,
                                    beat_2, beat_2,
                                    beat_2, beat_2,
                                    beat_4,
                                    beat_2, beat_2,
                                    beat_2, beat_2,
                                    beat_4,
                                    beat_2, beat_2,
                                    beat_4,
                                    beat_2, beat_2,
                                    beat_4,
};
const unsigned int note_num_JHT = 24;


#endif /* JUHUACAN_H_ */

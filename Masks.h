#ifndef MASKS_H
#define MASKS_H

short const I_brick[4][4][4] = {
                   {
                   {0, 0, 0, 0},
                   {1, 1, 1, 1},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0}
                              },

                   {
                   {0, 1, 0, 0},
                   {0, 1, 0, 0},
                   {0, 1, 0, 0},
                   {0, 1, 0, 0}
                              },

                   {
                   {0, 0, 0, 0},
                   {1, 1, 1, 1},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0}
                              },

                   {
                   {0, 1, 0, 0},
                   {0, 1, 0, 0},
                   {0, 1, 0, 0},
                   {0, 1, 0, 0}
                              }
                              };
short const J_brick[4][4][4] = {
                   {
                   {0, 2, 2, 0},
                   {0, 2, 0, 0},
                   {0, 2, 0, 0},
                   {0, 0, 0, 0}
                              },
                   {
                   {2, 0, 0, 0},
                   {2, 2, 2, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0}
                              },
                   {
                   {0, 2, 0, 0},
                   {0, 2, 0, 0},
                   {2, 2, 0, 0},
                   {0, 0, 0, 0}
                              },
                   {
                   {0, 0, 0, 0},
                   {2, 2, 2, 0},
                   {0, 0, 2, 0},
                   {0, 0, 0, 0}
                              }
                              };
short const L_brick[4][4][4] = {
                   {
                   {0, 3, 0, 0},
                   {0, 3, 0, 0},
                   {0, 3, 3, 0},
                   {0, 0, 0, 0}
                              },

                   {
                   {0, 0, 3, 0},
                   {3, 3, 3, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0}
                              },
                   {
                   {3, 3, 0, 0},
                   {0, 3, 0, 0},
                   {0, 3, 0, 0},
                   {0, 0, 0, 0}
                              },

                   {
                   {0, 0, 0, 0},
                   {3, 3, 3, 0},
                   {3, 0, 0, 0},
                   {0, 0, 0, 0}
                              }
                              };
short const S_brick[4][4][4] = {
                   {
                   {0, 4, 0, 0},
                   {0, 4, 4, 0},
                   {0, 0, 4, 0},
                   {0, 0, 0, 0}
                              },

                   {
                   {0, 0, 0, 0},
                   {0, 4, 4, 0},
                   {4, 4, 0, 0},
                   {0, 0, 0, 0}
                              },
                   {
                   {0, 4, 0, 0},
                   {0, 4, 4, 0},
                   {0, 0, 4, 0},
                   {0, 0, 0, 0}
                              },

                   {
                   {0, 0, 0, 0},
                   {0, 4, 4, 0},
                   {4, 4, 0, 0},
                   {0, 0, 0, 0}
                              }
                              };
short const Z_brick[4][4][4] = {
                   {
                   {0, 0, 5, 0},
                   {0, 5, 5, 0},
                   {0, 5, 0, 0},
                   {0, 0, 0, 0}
                              },

                   {
                   {0, 0, 0, 0},
                   {0, 5, 5, 0},
                   {0, 0, 5, 5},
                   {0, 0, 0, 0}
                              },
                   {
                   {0, 0, 5, 0},
                   {0, 5, 5, 0},
                   {0, 5, 0, 0},
                   {0, 0, 0, 0}
                              },

                   {
                   {0, 0, 0, 0},
                   {0, 5, 5, 0},
                   {0, 0, 5, 5},
                   {0, 0, 0, 0}
                              }
                              };
short const T_brick[4][4][4] = {
                   {
                   {0, 6, 0, 0},
                   {0, 6, 6, 0},
                   {0, 6, 0, 0},
                   {0, 0, 0, 0}
                              },

                   {
                   {0, 6, 0, 0},
                   {6, 6, 6, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0}
                              },
                   {
                   {0, 6, 0, 0},
                   {6, 6, 0, 0},
                   {0, 6, 0, 0},
                   {0, 0, 0, 0}
                              },

                   {
                   {0, 0, 0, 0},
                   {6, 6, 6, 0},
                   {0, 6, 0, 0},
                   {0, 0, 0, 0}
                              }
                              };
short const O_brick[4][4][4] = {
                   {
                   {0, 7, 7, 0},
                   {0, 7, 7, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0}
                              },

                   {
                   {0, 7, 7, 0},
                   {0, 7, 7, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0}
                              },
                   {
                   {0, 7, 7, 0},
                   {0, 7, 7, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0}
                              },

                   {
                   {0, 7, 7, 0},
                   {0, 7, 7, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0}
                              }
                              };
short static arena[21][12] =             {
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
      {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8}
                                         };
#endif //MASKS_H


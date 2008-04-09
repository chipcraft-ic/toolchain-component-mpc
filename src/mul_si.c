/* mpc_mul_si -- Multiply a complex number by a signed integer.

Copyright (C) 2005 Andreas Enge

This file is part of the MPC Library.

The MPC Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The MPC Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the MPC Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */

#include "gmp.h"
#include "mpfr.h"
#include "mpc.h"
#include "mpc-impl.h"

int
mpc_mul_si (mpc_ptr a, mpc_srcptr b, long int c, mpc_rnd_t rnd)
{
  int inex_re, inex_im;

  /* We could use mpfr_mul_si with newer versions of mpfr (2.1.0), but 
     not with the version contained in gmp-4.1.4. So copy and paste for 
     the time being                                                     */
  if (c >= 0)
  /* inlining by copy and paste */
  {
     inex_re = mpfr_mul_ui (MPC_RE(a), MPC_RE(b), (unsigned long int) c,
           MPC_RND_RE(rnd));
     inex_im = mpfr_mul_ui (MPC_IM(a), MPC_IM(b), (unsigned long int) c,
           MPC_RND_IM(rnd));
  }
  else
  {
     inex_re = -mpfr_mul_ui (MPC_RE(a), MPC_RE(b), (unsigned long int) (-c),
           INV_RND (MPC_RND_RE(rnd)));
     MPFR_CHANGE_SIGN (MPC_RE (a));
     inex_im = -mpfr_mul_ui (MPC_IM(a), MPC_IM(b), (unsigned long int) (-c),
           INV_RND (MPC_RND_IM(rnd)));
     MPFR_CHANGE_SIGN (MPC_IM (a));
  }
  
  return MPC_INEX(inex_re, inex_im);
}
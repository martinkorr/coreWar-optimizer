/* pMARS -- a portable Memory Array Redcode Simulator
 * Copyright (C) 1993-1996 Albert Ma, Na'ndor Sieben, Stefan Strack and Mintardjo Wangsawidjaja
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/*
 * config.h: user configuration
 * $Id: config.h,v 1.1.1.1 2000/08/20 13:29:30 iltzu Exp $
 *
 * This file contains preprocessor #define's that control compilation
 * of pMARS. You can control which pMARS binary is generated by uncommenting
 * these #define's or, preferably, by adding a -DSYMBOLNAME to CFLAGS in the
 * makefile.
 *
 * The most important switches are GRAPHX, SERVER, SMALLMEM, EXT94 and KEYPRESS.
 * The system specification switches are only important if you're trying to
 * to port pMARS to new platforms or use a non-standard C compiler.
 * The remaining preprocessor #define's can be altered to create your own
 * custom version of pMARS.
 */



/* ********************************************************************
   GRAPHX: pMARS supports a graphical core display on DOS and Unix
   machines as well as Macs.
   Displays are currently not supported for OS/2 and Amiga.
   A core display slows down simulation several-fold; it is therefore
   recommended to keep a no-display version of pMARS around for fights
   that last several rounds.

   Uncomment the next lines or add -DGRAPHX to CFLAGS to compile in a
   core display.
   ******************************************************************** */

/*
#ifndef GRAPHX
#define GRAPHX
#endif
*/

/* ********************************************************************
   SERVER: with this switch defined, a tournament version of pMARS without
   debugging support is created. The only reason to disable the debugger
   is to prevent its activation in non-interactive, KotH-style tournaments.
   The SERVER version is not measurably faster than the no-display version.
   GRAPHX and SERVER are mutually exclusive.
   ******************************************************************** */

/*
#ifndef SERVER
#define SERVER
#endif
*/

/* ********************************************************************
   SMALLMEM: makes all core addresses 16 bits wide as opposed to the default
   of 32 bits. This limits the core size to 65535 and slows simulation down
   by up to 30% depending on the platform, but it also drastically reduces
   the memory requirement of pMARS. SMALLMEM is recommended if you want to
   run large core, multi-warrior simulations on machines with limited memory
   or small memory caches. SMALLMEM-compiled pMARS runs actually faster on
   processors with a small primary cache like the Cyrix 486.
   ******************************************************************** */

/*
#ifndef SMALLMEM
#define SMALLMEM
#endif
*/

/* ********************************************************************
   EXT94: enables experimental additions to ICWS'94 that are not (yet)
   included in the standard draft. Currently, this includes the new opcodes
   NOP, SEQ, SNE and the A-field indirect addressing modes *, {, }
   as well as the P-space extensions LDP, STP, PIN.
   ******************************************************************** */

/*
#ifndef EXT94
#define EXT94
#endif
*/

/* ********************************************************************
   KEYPRESS: is only useful in conjunction with curses display libraries
   with broken support for interrupt handlers. Define KEYPRESS if you
   can't interrupt the core display with Ctrl-C to enter the debugger.
   With KEYPRESS defined, the debugger is entered whenever a key is pressed.
   Since this requires the SysV curses function wgetch(), KEYPRESS only works
   on SysV UNIX implementations.
   ******************************************************************** */

/*
#ifndef KEYPRESS
#define KEYPRESS
#endif
*/

/* ********************************************************************
   BSD44: If you run BSD Unix 4.4 or BSD 4.4 Lite and use the curses display
   library version 8.x, then you need to define this symbol. Curses 8.x has
   a windows structure that's slightly different from other curses libraries.
   ******************************************************************** */

/*
#ifndef BSD44
#define BSD44
#endif
*/

/* ********************************************************************
   HAVE_UNISTD_H: Define this if you have the header file "unistd.h" on your
   UNIX box. unistd.h is only used for the isatty prototype of the curses
   display
   ******************************************************************** */

#ifndef HAVE_UNISTD_H
#define HAVE_UNISTD_H
#endif

/* ********************************************************************
   HAVE_USLEEP: Define this if your OS has the 'usleep' system call.
   This is currently only used by the X11 interface.
   ******************************************************************** */

#ifndef HAVE_USLEEP
#define HAVE_USLEEP
#endif

/* ********************************************************************
   CLRSCR: is a string that is used by cdb to clear the screen with the
   "cls" command. It is not used in GRAPHX versions of pMARS. The
   default below works with vt10? terminals.
   ******************************************************************** */

#define CLRSCR "\033[;H\033[2J"

/* ********************************************************************
   XWINGRAPHX: If defined, specifies that pMARS should use the XWindows
    interface for graphical display. Specifying XWINGRAPHX overrides all
    other graphical displays (e.g. LINUXGRAPHX or CURSESGRAPHX)
   ******************************************************************** */

/*
#ifndef XWINGRAPHX
#define XWINGRAPHX
#endif
*/

/* ********************************************************************
   PMARSLANG: Currently, all messages are in English, but as soon as
    new translations of str_*.c come out, you can use this symbol to
    specify your choice of language
   ******************************************************************** */

#define PMARSLANG ENGLISH

/* ********************************************************************
   SYSTEM SPECIFICATION: Usually, these are predefined by your compiler.
   If not, you need to uncomment them or include them in CFLAGS.
   ******************************************************************** */

/* ********************************************************************
   MSDOS: Uncomment the next section if it is commented or compile with
   -D__MSDOS__
   ******************************************************************** */

/*
#ifndef __MSDOS__
#define __MSDOS__
#endif
*/

/* ********************************************************************
   CHECK386: enables a check for 386 or better machines. This is needed
   if you use Borland/Turbo C 3.0+ and tell the compiler to emit 386
   instructions.
   ******************************************************************** */

/*
#if defined(__TURBOC__) || defined(__BORLANDC__)

#ifndef CHECK386
#define CHECK386
#endif

#endif
*/

/* ********************************************************************
   OS/2: Uncomment the next section if it is commented or compile with
   -D__OS2__
   ******************************************************************** */

/*
#ifndef __OS2__
#define __OS2__
#endif
*/

/* ********************************************************************
   MAC: Uncomment the next section if it is commented or compile with
   -D__MAC__
   ******************************************************************** */

/*
#ifndef __MAC__
#define __MAC__
#endif
*/

/* ********************************************************************
   AMIGA: Uncomment the next section if it is commented or compile with
   -D__AMIGA__
   ******************************************************************** */

/*
#ifndef __AMIGA__
#define __AMIGA__
#endif
*/

/* ********************************************************************
   LINUX: You should use gcc and therefore __linux__ should already be
    defined. If you specified GRAPHX, the SVGA version will be built by
    default. Define CURSESGRAPHX to override this option and build pmars
    with curses display.
   ******************************************************************** */

/*
#ifndef __linux__
#define __linux__
#endif
*/

/* ******************************************************************
   The following controls the default aspects in the game. Hopefully
   their names are descriptive.
   ****************************************************************** */

#define DEFAULTWARRIOR    2
#define DEFAULTCORESIZE   8000
#define DEFAULTTASKNUM    8000
#define DEFAULTINSTRLIM   100
#define DEFAULTSEPARATION 100
#define DEFAULTROUNDS     1
/* 'l' or 'L' is required if the number is bigger than 32767 */
#define DEFAULTCYCLES     80000L
#define DEFAULTSCORE "(W*W-1)/S"/* formula used for score calculation */

/* ********************************************************************
   Do not alter the next sections. They mainly ensure consistency.
   ******************************************************************** */

#if (defined(__TURBOC__) || defined(__BORLANDC__) || defined(MSDOS)\
    || defined(__MSDOS__) || defined(_MSC_VER)) && !defined(__GO32__)\
    && !defined(WATCOM)
#define DOS16
#endif

#if defined(__DECC)                /* DEC C works, VAX C doesn't */
#define VMS
#endif

#if defined(__GO32__) && !defined(DJGPP)
#define DJGPP
#endif

#if (defined(DOSTXTGRAPHX) && defined(DOSGRXGRAPHX)) || defined(OS2PMGRAPHX)\
    || defined(MACGRAPHX) || defined(CURSESGRAPHX) || defined(DOSALLGRAPHX)\
     || defined(LINUXGRAPHX) || defined(XWINGRAPHX)
#ifndef GRAPHX
#define GRAPHX
#endif
#endif

#if defined(__MSDOS__) && defined(GRAPHX)
#ifndef DOSALLGRAPHX
#define DOSALLGRAPHX
#endif
#endif                                /* __MSDOS__ && GRAPHX */

#if defined(DOSTXTGRAPHX) && defined(DOSGRXGRAPHX)
#define DOSALLGRAPHX
#else
#if defined(DOSALLGRAPHX)
#define DOSTXTGRAPHX
#define DOSGRXGRAPHX
#endif                                /* ALL */
#endif

#if defined(__MPC__) || defined(THINK_C) || defined(MPW)
#ifndef __MAC__
#define __MAC__
#endif
#ifdef GRAPHX
#define MACGRAPHX
#endif
#endif

#if defined(GRAPHX) && defined(unix) && !defined(DJGPP) && !defined(__linux__)
#ifndef CURSESGRAPHX
#define CURSESGRAPHX
#endif
#endif                                /* GRAPHX && unix */

#if defined(GRAPHX) && defined(__linux__)
#ifndef LINUXGRAPHX
#ifndef CURSESGRAPHX
#define LINUXGRAPHX
#endif
#else
#ifdef CURSESGRAPHX
#undef CURSESGRAPHX
#endif
#endif
#endif

#ifdef CURSESGRAPHX
#ifndef DOSTXTGRAPHX
#define DOSTXTGRAPHX
#endif
#endif

#if defined(__OS2__) && defined(GRAPHX)
#ifndef OS2PMGRAPHX
#define OS2PMGRAPHX
#endif
#endif

#if defined(GRAPHX)
#ifdef SERVER
#undef SERVER
#endif
#endif

#if defined(XWINGRAPHX)
#ifdef CURSESGRAPHX
#undef CURSESGRAPHX
#endif
#ifdef LINUXGRAPHX
#undef LINUXGRAPHX
#endif
#ifdef DOSTXTGRAPHX
#undef DOSTXTGRAPHX
#endif
#endif

#if defined(EXT94)
#define NEW_OPCODES
#define NEW_MODES
/* delete the next two lines if you don't want LDP, STP, PIN */
#define PSPACE
#define SHARED_PSPACE
#endif

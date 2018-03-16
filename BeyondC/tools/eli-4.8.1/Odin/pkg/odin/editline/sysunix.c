/*  $Revision: 1.2 $
**
**  Unix system-dependant routines for editline library.
*/
#include "editline.h"

#ifdef HAVE_TERMIOS_H
#include <termios.h>

void
rl_ttyset(
  GMC_ARG(int, Reset)
  )
  GMC_DCL(int, Reset)
{
    static struct termios	old;
    struct termios		newval;

    if (Reset == 0) {
	(void)tcgetattr(0, &old);
	rl_erase = old.c_cc[VERASE];
	rl_kill = old.c_cc[VKILL];
	rl_eof = old.c_cc[VEOF];
	rl_intr = old.c_cc[VINTR];
	rl_quit = old.c_cc[VQUIT];
#ifdef DO_SIGTSTP
	rl_susp = old.c_cc[VSUSP];
#endif	/* defined(DO_SIGTSTP) */

	newval = old;
	newval.c_lflag &= ~(ECHO | ICANON | ISIG);
	newval.c_iflag &= ~(ISTRIP | INPCK);
	newval.c_cc[VMIN] = 1;
	newval.c_cc[VTIME] = 0;
	(void)tcsetattr(0, TCSADRAIN, &newval);
    }
    else
	(void)tcsetattr(0, TCSADRAIN, &old);
}

#else
#ifdef HAVE_TERMIO_H
#include <termio.h>

void
rl_ttyset(
  GMC_ARG(int, Reset)
  )
  GMC_DCL(int, Reset)
{
    static struct termio	old;
    struct termio		newval;

    if (Reset == 0) {
	(void)ioctl(0, TCGETA, &old);
	rl_erase = old.c_cc[VERASE];
	rl_kill = old.c_cc[VKILL];
	rl_eof = old.c_cc[VEOF];
	rl_intr = old.c_cc[VINTR];
	rl_quit = old.c_cc[VQUIT];
#ifdef DO_SIGTSTP
	rl_susp = old.c_cc[VSUSP];
#endif	/* defined(DO_SIGTSTP) */

	newval = old;
	newval.c_lflag &= ~(ECHO | ICANON | ISIG);
	newval.c_iflag &= ~(ISTRIP | INPCK);
	newval.c_cc[VMIN] = 1;
	newval.c_cc[VTIME] = 0;
	(void)ioctl(0, TCSETAW, &newval);
    }
    else
	(void)ioctl(0, TCSETAW, &old);
}

#else
#include <sgtty.h>

void
rl_ttyset(
  GMC_ARG(int, Reset)
  )
  GMC_DCL(int, Reset)
{
    static struct sgttyb	old_sgttyb;
    static struct tchars	old_tchars;
    struct sgttyb		new_sgttyb;
    struct tchars		new_tchars;
#ifdef DO_SIGTSTP
    struct ltchars		old_ltchars;
#endif	/* defined(DO_SIGTSTP) */

    if (Reset == 0) {
	(void)ioctl(0, TIOCGETP, &old_sgttyb);
	rl_erase = old_sgttyb.sg_erase;
	rl_kill = old_sgttyb.sg_kill;

	(void)ioctl(0, TIOCGETC, &old_tchars);
	rl_eof = old_tchars.t_eofc;
	rl_intr = old_tchars.t_intrc;
	rl_quit = old_tchars.t_quitc;

#ifdef DO_SIGTSTP
	(void)ioctl(0, TIOCGLTC, &old_ltchars);
	rl_susp = old_ltchars.t_suspc;
#endif	/* defined(DO_SIGTSTP) */

	new_sgttyb = old_sgttyb;
	new_sgttyb.sg_flags &= ~ECHO;
	new_sgttyb.sg_flags |= RAW;
#ifdef PASS8
	new_sgttyb.sg_flags |= PASS8;
#endif	/* defined(PASS8) */
	(void)ioctl(0, TIOCSETP, &new_sgttyb);

	new_tchars = old_tchars;
	new_tchars.t_intrc = -1;
	new_tchars.t_quitc = -1;
	(void)ioctl(0, TIOCSETC, &new_tchars);
    }
    else {
	(void)ioctl(0, TIOCSETP, &old_sgttyb);
	(void)ioctl(0, TIOCSETC, &old_tchars);
    }
}
#endif	/* !defined(HAVE_TERMIO_H) */
#endif	/* !defined(HAVE_TERMIOS_H) */

void
rl_add_slash(
  GMC_ARG(char*, path),
  GMC_ARG(char*, p)
  )
  GMC_DCL(char*, path)
  GMC_DCL(char*, p)
{
    struct stat	Sb;

    if (stat(path, &Sb) >= 0)
	(void)strcat(p, S_ISDIR(Sb.st_mode) ? "/" : " ");
}

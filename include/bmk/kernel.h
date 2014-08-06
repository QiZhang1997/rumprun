#ifndef _LOCORE

#include <bmk/types.h>

#include <arch/i386/md.h>

#define MEMSTART 0x100000
#define PAGE_SIZE 0x1000
#define STACK_SIZE 0x2000

#define round_page(x) (((x) + (PAGE_SIZE-1)) & ~(PAGE_SIZE-1))
#define trunc_page(x) ((x) & ~(PAGE_SIZE-1))

#define assert(x) \
  do { \
    if (!(x)) { \
        bmk_cons_puts("assert \"" #x "\" FAILED\n"); for (;;); \
    } \
  } while (0)

void *bmk_allocpg(size_t);

#define panic(x) do { bmk_cons_puts(x "\n"); for (;;); } while (0)

/* eh eh eh.  NOTE: callable only after rump_init() has run! */
#define bmk_printf(x, ...) \
    do { \
	void rump_schedule(void); void rump_unschedule(void); \
	int rumpns_printf(const char *, ...); \
	rump_schedule(); rumpns_printf(x, __VA_ARGS__); rump_unschedule(); \
    } while (0);

void bmk_cons_puts(const char *);
void bmk_cons_putc(int);

void bmk_app_main(void);

void bmk_cpu_init(void);
void bmk_cpu_nanohlt(void);

void bmk_isr_clock(void);
void bmk_isr_net(void);
int bmk_isr_netinit(int (*)(void *), void *);

#endif /* _LOCORE */

#define ENOMEM		1
#define EBUSY		2
#define EINVAL		3
#define EGENERIC	EINVAL
#define ETIMEDOUT	4

#define ENTRY(x)	.text; .globl x; .type x,@function; x:
#define END(x)		.size x, . - x

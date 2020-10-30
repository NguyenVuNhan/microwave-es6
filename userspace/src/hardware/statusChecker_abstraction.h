#ifndef __STATUS_CHECKER_ABSTRACTION_H

#define __STATUS_CHECKER_ABSTRACTION_H

/* read all buttons: */
/* /dev/microwave_buttons */
/* all buttons can be 1 or 0 */

#include <string>

class IStatusChecker
{
public:
    virtual ~IStatusChecker() {};
    virtual int getTimeDial() = 0;
    virtual int getButtons()  = 0;
};

#endif // ifndef __STATUS_CHECKER_ABSTRACTION_H

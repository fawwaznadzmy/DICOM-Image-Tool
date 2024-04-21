#include "app.h"
#include "frame.h"

 bool App::OnInit()
{
    AppFrame *frame = new AppFrame();
    frame->Show(true);
    return true;
}
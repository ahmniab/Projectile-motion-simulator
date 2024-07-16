#include "text_box.h"
#include "stdlib.h"

Text_box *create_new_text_box\
(\
    int max_len ,\
    Font *text_font ,\
    float font_size,\
    float spacing,\
    Color backgrond_color ,\
    Color border_color ,\
    Color border_color_on_hover, \
    Color Text_color,\
    float x , float y ,\
    float width , float height\
)
{
    Text_box *new_text_box = (Text_box*) malloc(sizeof(Text_box));

    new_text_box->max_len = max_len;
    new_text_box->len = 0;
    new_text_box->buff = (char*)calloc(max_len + 1 , sizeof(char) );

    new_text_box->backgrond_color = backgrond_color;
    new_text_box->border_color = border_color ;
    new_text_box->text_color = Text_color ;
    new_text_box->border_color_on_hover = border_color_on_hover ;

    new_text_box->text_font = text_font  ;
    new_text_box->font_size = font_size  ;
    new_text_box->spacing = spacing  ;

    new_text_box->textbox_rectangle.x = x  ;
    new_text_box->textbox_rectangle.y = y  ;
    new_text_box->textbox_rectangle.width = width  ;
    new_text_box->textbox_rectangle.height = height  ;
    new_text_box->mouseOnText = false;

    return new_text_box;

}

void draw_text_box(Text_box *ptbx){

    if (CheckCollisionPointRec(GetMousePosition(), ptbx->textbox_rectangle)) ptbx->mouseOnText = true;
        else ptbx->mouseOnText = false;

        if (ptbx->mouseOnText)
        {
            // SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (ptbx->len < ptbx->max_len))
                {
                    ptbx->buff[ptbx->len] = (char)key;
                    ptbx->buff[ptbx->len+1] = '\0'; // Add null terminator at the end of the string.
                    ptbx->len++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                ptbx->len--;
                if (ptbx->len < 0) ptbx->len = 0;
                ptbx->buff[ptbx->len] = '\0';
            }
        }
        // else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (ptbx->mouseOnText) ptbx->framesCounter++;
        else ptbx->framesCounter = 0;

    DrawRectangleRec(ptbx->textbox_rectangle, ptbx->backgrond_color);
    if (ptbx->mouseOnText) DrawRectangleLines((int)ptbx->textbox_rectangle.x, (int)ptbx->textbox_rectangle.y, (int)ptbx->textbox_rectangle.width, (int)ptbx->textbox_rectangle.height, ptbx->border_color_on_hover);
    else DrawRectangleLines((int)ptbx->textbox_rectangle.x, (int)ptbx->textbox_rectangle.y, (int)ptbx->textbox_rectangle.width, (int)ptbx->textbox_rectangle.height, ptbx->border_color);
    
    // DrawText(ptbx->buff, (int)textBox.x + 5, (int)textBox.y + 8, 40, ptbx->text_color);
    DrawTextEx(*(ptbx->text_font), ptbx->buff, (Vector2){ptbx->textbox_rectangle.x+5 , ptbx->textbox_rectangle.y+8}, ptbx->font_size, ptbx->spacing, ptbx->text_color);
    if (ptbx->mouseOnText)
    {
        if (ptbx->len < ptbx->max_len)
        {
            // Draw blinking underscore char
            if (((ptbx->framesCounter/30)%2) == 0) DrawTextEx(*(ptbx->text_font),"|", (Vector2){ptbx->textbox_rectangle.x + 8 + MeasureTextEx(*(ptbx->text_font), ptbx->buff, ptbx->font_size, ptbx->spacing).x,ptbx->textbox_rectangle.y + 12}, ptbx->font_size, ptbx->spacing ,ptbx->text_color);
        }
        // else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
    }

}

void free_text_box(Text_box *ptb){
    free(ptb->buff);
    free(ptb);
}
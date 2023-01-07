#include "stdafx.h"
#include "Input.h"
#include <stdio.h>

void PrintModifiers(Uint16 mod);

void PrintKeyInfo(SDL_KeyboardEvent* key) {
  /* Is it a release or a press? */
  if (key->type == SDL_KEYUP)
    printf("Release:- ");
  else
    printf("Press:- ");

  /* Print the hardware scancode first */
  printf("Scancode: 0x%02X", key->keysym.scancode);
  /* Print the name of the key */
  printf(", Name: %s", SDL_GetKeyName(key->keysym.sym));
  /* We want to print the unicode info, but we need to make */
  /* sure its a press event first (remember, release events */
  /* don't have unicode info                                */
  if (key->type == SDL_KEYDOWN) {
    /* If the Unicode value is less than 0x80 then the    */
    /* unicode value can be used to get a printable       */
    /* representation of the key, using (char)unicode.    */
    //printf(", 
    //printf(", Unicode: ");
    /* if (key->keysym.unicode < 0x80 && key->keysym.unicode > 0) {
       printf("%c (0x%04X)", (char)key->keysym.unicode,
         key->keysym.unicode);
     }
     else {
       printf("? (0x%04X)", key->keysym.unicode);
     }*/
  }
  printf("\n");
  /* Print modifier info */
  PrintModifiers(key->keysym.mod);
}

/* Print modifier info */
void PrintModifiers(Uint16 mod) {
  printf("Modifers: ");

  /* If there are none then say so and return */
  if (mod == KMOD_NONE) {
    printf("None\n");
    return;
  }

  /* Check for the presence of each SDLMod value */
  /* This looks messy, but there really isn't    */
  /* a clearer way.                              */
  if (mod & KMOD_NUM) printf("NUMLOCK ");
  if (mod & KMOD_CAPS) printf("CAPSLOCK ");
  if (mod & KMOD_LCTRL) printf("LCTRL ");
  if (mod & KMOD_RCTRL) printf("RCTRL ");
  if (mod & KMOD_RSHIFT) printf("RSHIFT ");
  if (mod & KMOD_LSHIFT) printf("LSHIFT ");
  if (mod & KMOD_RALT) printf("RALT ");
  if (mod & KMOD_LALT) printf("LALT ");
  if (mod & KMOD_CTRL) printf("CTRL ");
  if (mod & KMOD_SHIFT) printf("SHIFT ");
  if (mod & KMOD_ALT) printf("ALT ");
  printf("\n");
}

namespace SDL
{
  bool Input::isKeyDown(SDL_Keycode key)
  {
    return m_codes.find(key) != m_codes.end();
  }

  void Input::update()
  {
    SDL_Event event;
    SDL_Keycode code = -1;
    m_codes.clear();
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        /* Keyboard event */
        /* Pass the event data onto PrintKeyInfo() */
      case SDL_KEYDOWN:
        auto symbol = event.key.keysym.sym;
        if (symbol != 0)
          m_codes.insert(symbol);

        break;
      }
    }
  }
}
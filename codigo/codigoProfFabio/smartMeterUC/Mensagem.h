#ifndef _MENSAGEM_
#define _MENSAGEM_
#include "definicoes.h"

#include <inttypes.h>

#include <string>
#pragma pack(1);
#define QTD_FRAG 5


typedef struct {
  uint8_t   TIPO;
  uint32_t  ENERGIA1;
  uint32_t  ENERGIA2;
  uint32_t  TIMESTAMP;
  uint32_t  MEDIDOR;
  uint8_t   ASSINATURA[56]; 
  uint8_t   filler[2]; 




}TipoMensagem;

class Mensagem {

  private: 
    uint8_t dados[QTD_FRAG][20];
    uint8_t contador_mensagens;
    uint8_t ultimo_pedaco_enviado;
    uint8_t fezInit;

  public:
    Mensagem();
     uint8_t getMSGn(void);
    int getQtd(void);
    int temMensagem(void);
    void update(TipoMensagem  M);
    void getFragment (std::string &s);

 
};

#endif

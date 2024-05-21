#include "Mensagem.h"

Mensagem::Mensagem ()
{
  fezInit = 0;
  contador_mensagens=0;
  ultimo_pedaco_enviado=0;
  for (int l=0; l< QTD_FRAG; l++)
  {
    dados[l][0]=l;
    for (int c=1;c<15;c++) dados[l][c]=65;
  }
}

uint8_t Mensagem::getMSGn (void)
{
    return contador_mensagens;

}
int Mensagem::temMensagem (void)
{
  return fezInit;
}

int Mensagem::getQtd (void)
{
  return QTD_FRAG;
}
void Mensagem::getFragment (std::string &s )
{
    s.clear();
    for (int a=0;a<16;a++) s.insert(a,1,dados[ultimo_pedaco_enviado][a]);
    ultimo_pedaco_enviado = (ultimo_pedaco_enviado +1 ) % getQtd();
    
         
}

void Mensagem::update (TipoMensagem M)
{
  
   fezInit=1;
  
  uint8_t *ptr = (uint8_t *) &M;
  uint8_t qtd = getQtd();
  
  
   for (uint8_t pedaco=0;pedaco< qtd;pedaco++)
   {
      dados[pedaco][0] = contador_mensagens++;
      if (contador_mensagens==40) contador_mensagens=0;
      for ( int a=0;a<15;a++)
      {   
          dados[pedaco][a+1]=ptr[pedaco*15+a];
      }
   }
   
              
      
}

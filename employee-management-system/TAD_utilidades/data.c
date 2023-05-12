#include <time.h> //necessário para usar localtime() e struct tm
#include "data.h"

struct data {
   int dia;
   int mes;
   int ano;
};

Data *get_data(void) { 
    Data* data = (Data*) malloc(sizeof(Data)); 
    
    //ponteiro para struct que armazena data e hora  
    struct tm *data_hora_atual;     
    
    //variável do tipo time_t para armazenar o tempo em segundos  
    time_t segundos;
    
    //obtendo o tempo em segundos (funcao vinda da time.h) 
    time(&segundos);   
    
    //para converter de segundos para o tempo local  
    //utilizamos a função localtime  
    data_hora_atual = localtime(&segundos);
    
    data->dia = data_hora_atual->tm_mday;
    data->mes = data_hora_atual->tm_mon+1;
    data->ano = data_hora_atual->tm_year+1900;

    return data;
}
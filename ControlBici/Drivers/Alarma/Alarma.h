#ifndef ALARMA_CONTROL_H_
#define ALARMA_CONTROL_H_

#define SEGUNDOS_POR_MINUTO 60

void IntegridadCadenaInterface (void * paramSemaforo);
void MedidorPulsacionCardiacaInterface (void * paramCola);
void BotonActivacionAlarmaInterface (void * paramSemaforo);
void SirenaInterface (void * paramColaControlSirena);

#endif /* ALARMA_CONTROL_H_ */

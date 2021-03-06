

#include <rtthreads.h>
#include <stdlib.h>

void setup() 
{
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);     //LED
}

THREAD* th1=NULL;
int handler=0;
int aux=0;
int aux_t=0;
void periodic_task1() 
{
  static uint32_t counter=0;
  counter++;
  Serial.print("[T1] THREAD 1------\n  current time(us): \t \t");  
  Serial.print(thread_get_time());  
  Serial.print("\n   error handler:\t");  
  Serial.println(handler);
  Serial.print("\n   auxt:\t");  
  Serial.println(aux_t);
  
  aux=0;
  thread_ATS_enable();
  aux=1;
  //thread_ATS_disable();
  thread_ATS_signal(th1);
  aux=2;
  thread_ATS_disable();
  aux=3;

}

void error_handler_task1(int what)
{
  //Serial.print("[T1] EATS------\t"); 
  if(what==SIMPLERTFRAMEWORK_ATS_SIGNAL)
    handler++;
    aux_t=aux;
  /*while (1)
  {
  }
 */
 
}

extern unsigned int __heap_start;
extern void *__brkval;


void loop() { 
  
  Serial.print("Simple TESTs \n");  
  
  unsigned long t1=micros();
  unsigned long t2=micros();
  int mem1=(int)__brkval;
  int mem2=(int)__brkval;
  
  t2=t2-t1;
  Serial.print("error_(us)\t");    
  Serial.println(t2);  

  mem1=(int)__brkval;
  t1=micros();
  THREAD* th1=periodic_thread_create(&periodic_task1, NULL, NULL, 200, 0, 0, 1000000, 1000000, 500000, &error_handler_task1);
  t2=micros();
  mem2=(int)__brkval;
  t2=t2-t1;
  mem2=mem2-mem1;  
  Serial.print("1_hilo_(us)\t");    
  Serial.println(t2);  
  Serial.print("1_hilo_(bytes)\t");    
  Serial.println(mem2);  
  
 
  mem1=(int)__brkval;
  t1=micros();
  THREAD* th2=periodic_thread_create(&periodic_task1, NULL, NULL, 200, 0, 0, 1000000, 1000000, 500000, &error_handler_task1);
  t2=micros();
  mem2=(int)__brkval;
  t2=t2-t1;
  mem2=mem2-mem1;  
  Serial.print("2_hilo_(us)\t");    
  Serial.println(t2);  
  Serial.print("2_hilo_(bytes)\t");    
  Serial.println(mem2);  


  mem1=(int)__brkval;
  t1=micros();
  //thread_remove(th1);
  t2=micros();
  mem2=(int)__brkval;
  t2=t2-t1;
  mem2=mem2-mem1;  
  Serial.print("2_hilo_removed(us)\t");    
  Serial.println(t2);  
  Serial.print("2_hilo_removed(bytes)\t");    
  Serial.println(mem2);  


  /* thread signal*/
  
  mem1=(int)__brkval;
  t1=micros();
  thread_signal(th1);
  t2=micros();
  mem2=(int)__brkval;
  t2=t2-t1;
  mem2=mem2-mem1;  
  Serial.print("thread_signal_(us)\t");    
  Serial.println(t2);  
  Serial.print("trhreadsignal_(bytes)\t");    
  Serial.println(mem2);  
  
  /* ATS*/
  
  mem1=(int)__brkval;
  t1=micros();
  thread_ATS_enable();
  t2=micros();
  mem2=(int)__brkval;
  t2=t2-t1;
  mem2=mem2-mem1;  
  Serial.print("thread_ATS_enable_(us)\t");    
  Serial.println(t2);  
  Serial.print("thread_ATS_enable_(bytes)\t");    
  Serial.println(mem2);  
 
  mem1=(int)__brkval;
  t1=micros();
  thread_ATS_disable();
  t2=micros();
  mem2=(int)__brkval;
  t2=t2-t1;
  mem2=mem2-mem1;  
  Serial.print("thread_ATS_disable_(us)\t");    
  Serial.println(t2);  
  Serial.print("thread_ATS_disable_(bytes)\t");    
  Serial.println(mem2);  
 
  mem1=(int)__brkval;
  t1=micros();
  thread_ATS_signal(th1);
  t2=micros();
  mem2=(int)__brkval;
  t2=t2-t1;
  mem2=mem2-mem1;  
  Serial.print("thread_ATS_signal_(us)\t");    
  Serial.println(t2);  
  Serial.print("thread_ATS_signal_(bytes)\t");    
  Serial.println(mem2); 
  
  /*
  mem1=(int)__brkval;
  t1=micros();
  //thread_ATS_set_maximum(1);
  t2=micros();
  mem2=(int)__brkval;
  t2=t2-t1;
  mem2=mem2-mem1;  
  Serial.print("thread_ATS_set_max_(us)\t");    
  Serial.println(t2);  
  Serial.print("thread_ATS_set_max_(bytes)\t");    
  Serial.println(mem2); 
  
  
  mem1=(int)__brkval;
  t1=micros();
 // thread_ATS_get_maximum();
  t2=micros();
  mem2=(int)__brkval;
  t2=t2-t1;
  mem2=mem2-mem1;  
  Serial.print("thread_ATS_get_max_(us)\t");    
  Serial.println(t2);  
  Serial.print("thread_ATS_get_max_(bytes)\t");    
  Serial.println(mem2); 
 */
 
  
  /* queue tests**/
  QUEUE*  queue;
  
  mem1=(int)__brkval;
  t1=micros();
  queue=thread_queue_create(100); 
  t2=micros();
  mem2=(int)__brkval;
  t2=t2-t1;
  mem2=mem2-mem1;
  Serial.print("queue_create_100_(us)\t");    
  Serial.println(t2);  
  Serial.print("queue_create_100_(bytes)\t");    
  Serial.println(mem2);  
  
 
  mem1=(int)__brkval;
  t1=micros();
  queue=thread_queue_create(10); 
  t2=micros();
  mem2=(int)__brkval;
  t2=t2-t1;
  mem2=mem2-mem1;  
  Serial.print("queue_create_10_(us)\t");    
  Serial.println(t2);  
  Serial.print("queue_create_10_(bytes)\t");    
  Serial.println(mem2);  

  mem1=(int)__brkval;
  t1=micros();
  thread_queue_nb_set_element( queue, queue); 
  t2=micros();
  mem2=(int)__brkval;
  mem2=mem2-mem1;  
  t2=t2-t1;
  Serial.print("set_element(us)\t");    
  Serial.println(t2);  
  Serial.print("set_element(bytes)\t");    
  Serial.println(mem2);  


  mem1=(int)__brkval;
  t1=micros();
  thread_queue_nb_get_element(queue); 
  t2=micros();
  mem2=(int)__brkval;
  mem2=mem2-mem1;  
  t2=t2-t1;
  Serial.print("get_element(us)\t");    
  Serial.println(t2);  
  Serial.print("get_element(bytes)\t");    
  Serial.println(mem2);  
  
  
  
  mem1=(int)__brkval;
  t1=micros();
  thread_queue_delete(queue); 
  t2=micros();
  mem2=(int)__brkval;
  mem2=mem2-mem1;  
  t2=t2-t1;
  Serial.print("queue_remove(us)\t");    
  Serial.println(t2);  
  Serial.print("queue_remove(bytes)\t");    
  Serial.println(mem2);  
  
  /****/
  /**SEMAPHORE**/
  
  
  SEMAPHORE*  sem12;
  
  mem1=(int)__brkval;
  t1=micros();
  sem12=thread_semaphore_create(10); 
  t2=micros();
  mem2=(int)__brkval;
  t2=t2-t1;
  mem2=mem2-mem1;
  Serial.print("sem_create_10_(us)\t");    
  Serial.println(t2);  
  Serial.print("sem_create_10_(bytes)\t");    
  Serial.println(mem2);  
  
  
  mem1=(int)__brkval;
  t1=micros();
  thread_semaphore_P(sem12); 
  t2=micros();
  mem2=(int)__brkval;
  t2=t2-t1;
  mem2=mem2-mem1;
  Serial.print("sem_P(us)\t");    
  Serial.println(t2);  
  Serial.print("sem_P(bytes)\t");    
  Serial.println(mem2);  
  
  
  mem1=(int)__brkval;
  t1=micros();
  thread_semaphore_V(sem12); 
  t2=micros();
  mem2=(int)__brkval;
  t2=t2-t1;
  mem2=mem2-mem1;
  Serial.print("sem_V(us)\t");    
  Serial.println(t2);  
  Serial.print("sem_V(bytes)\t");    
  Serial.println(mem2);  
  
  mem1=(int)__brkval;
  t1=micros();
  thread_semaphore_free(sem12); 
  t2=micros();
  mem2=(int)__brkval;
  t2=t2-t1;
  mem2=mem2-mem1;
  Serial.print("sem_free(us)\t");    
  Serial.println(t2);  
  Serial.print("sem_free(bytes)\t");    
  Serial.println(mem2);  
  
  

  mem1=(int)__brkval;
  t1=micros();
  SIMPLERTFRAMEWORK_ATOMIC_SECTION{
    int atomic=5;
  }
  t2=micros();
  mem2=(int)__brkval;
  t2=t2-t1;
  mem2=mem2-mem1;
  Serial.print("ATOMIC_BLOCK(us)\t");    
  Serial.println(t2);  
  Serial.print("ATOMIC_BLOCK(bytes)\t");    
  Serial.println(mem2);  
  
  
  /****/
  //thread_malloc;
  
  mem1=(int)__brkval;
  t1=micros();
  void* data_malloc=thread_malloc(10);
  t2=micros();
  mem2=(int)__brkval;
  mem2=mem2-mem1;  
  t2=t2-t1;
  Serial.print("malloc_10(us)\t");    
  Serial.println(t2);  
  Serial.print("malloc_10(bytes)\t");    
  Serial.println(mem2);  
  
  mem1=(int)__brkval;
  t1=micros();
  thread_free(data_malloc);
  t2=micros();
  mem2=(int)__brkval;
  mem2=mem2-mem1;  
  t2=t2-t1;
  Serial.print("free_10)\t");    
  Serial.println(t2);  
  Serial.print("free_10(bytes)\t");    
  Serial.println(mem2);  
 
  mem1=(int)__brkval;
  t1=micros();
  data_malloc=thread_malloc(100);
  t2=micros();
  mem2=(int)__brkval;
  mem2=mem2-mem1;  
  t2=t2-t1;
  Serial.print("malloc_100(us)\t");    
  Serial.println(t2);  
  Serial.print("malloc_100(bytes)\t");    
  Serial.println(mem2);
  
  
  mem1=(int)__brkval;
  t1=micros();
  thread_free(data_malloc);
  t2=micros();
  mem2=(int)__brkval;
  mem2=mem2-mem1;  
  t2=t2-t1;
  Serial.print("free_100(us)\t");    
  Serial.println(t2);  
  Serial.print("free_100(bytes)\t");    
  Serial.println(mem2);
  

/****/
/*time*/

//uint32_t thread_get_time();

  mem1=(int)__brkval;
  t1=micros();
  thread_get_time();
  t2=micros();
  mem2=(int)__brkval;
  mem2=mem2-mem1;  
  t2=t2-t1;
  Serial.print("get_time(us)\t");    
  Serial.println(t2);  
  Serial.print("gettime(bytes)\t");    
  Serial.println(mem2);
  

  mem1=(int)__brkval;
  t1=micros();
  thread_get_error_in_time();
  t2=micros();
  mem2=(int)__brkval;
  mem2=mem2-mem1;  
  t2=t2-t1;
  Serial.print("get_error(us)\t");    
  Serial.println(t2);  
  Serial.print("get_errot (bytes)\t");    
  Serial.println(mem2);
  
  
/****/
/*read*/
  
  uint32_t data_int;
  float data_float;
  
  mem1=(int)__brkval;
  t1=micros();
  thread_read_byte((uint32_t) &data_int);
  t2=micros();
  mem2=(int)__brkval;
  mem2=mem2-mem1;  
  t2=t2-t1;
  Serial.print("read_byte(us)\t");    
  Serial.println(t2);  
  Serial.print("read_byte (bytes)\t");    
  Serial.println(mem2);
  
  
  mem1=(int)__brkval;
  t1=micros();
  thread_read_uint16_t((uint32_t) &data_int);
  t2=micros();
  mem2=(int)__brkval;
  mem2=mem2-mem1;  
  t2=t2-t1;
  Serial.print("read_uint16_t(us)\t");    
  Serial.println(t2);  
  Serial.print("read_uint16_t(bytes)\t");    
  Serial.println(mem2);
   
    
  mem1=(int)__brkval;
  t1=micros();
  thread_read_uint32_t((uint32_t) &data_int);
  t2=micros();
  mem2=(int)__brkval;
  mem2=mem2-mem1;  
  t2=t2-t1;
  Serial.print("read_uint32_t(us)\t");    
  Serial.println(t2);  
  Serial.print("read_uint32_t(bytes)\t");    
  Serial.println(mem2);
  
  mem1=(int)__brkval;
  t1=micros();
  thread_read_float((uint32_t) &data_float);
  t2=micros();
  mem2=(int)__brkval;
  mem2=mem2-mem1;  
  t2=t2-t1;
  Serial.print("read_float(us)\t");    
  Serial.println(t2);  
  Serial.print("read_float(bytes)\t");    
  Serial.println(mem2);
  
  
  
  /* write */  
  mem1=(int)__brkval;
  t1=micros();
  thread_write_byte((uint32_t) &data_int, 0);
  t2=micros();
  mem2=(int)__brkval;
  mem2=mem2-mem1;  
  t2=t2-t1;
  Serial.print("write_byte(us)\t");    
  Serial.println(t2);  
  Serial.print("write_byte (bytes)\t");    
  Serial.println(mem2);
  
  
  mem1=(int)__brkval;
  t1=micros();
  thread_write_uint16_t((uint32_t) &data_int,0);
  t2=micros();
  mem2=(int)__brkval;
  mem2=mem2-mem1;  
  t2=t2-t1;
  Serial.print("write_uint16_t(us)\t");    
  Serial.println(t2);  
  Serial.print("write_uint16_t(bytes)\t");    
  Serial.println(mem2);
   
    
  mem1=(int)__brkval;
  t1=micros();
  thread_read_uint32_t((uint32_t) &data_int);
  t2=micros();
  mem2=(int)__brkval;
  mem2=mem2-mem1;  
  t2=t2-t1;
  Serial.print("write_uint32_t(us)\t");    
  Serial.println(t2);  
  Serial.print("write_uint32_t(bytes)\t");    
  Serial.println(mem2);
  
  mem1=(int)__brkval;
  t1=micros();
  thread_read_float((uint32_t) &data_float);
  t2=micros();
  mem2=(int)__brkval;
  mem2=mem2-mem1;  
  t2=t2-t1;
  Serial.print("write_float(us)\t");    
  Serial.println(t2);  
  Serial.print("write_float(bytes)\t");    
  Serial.println(mem2);

    
    
/*float	thread_read_float(uint32_t position); 
uint16_t thread_read_uint16_t(uint32_t position); 
uint32_t thread_read_uint32_t(uint32_t position); 

void  thread_write_byte(uint32_t position, uint8_t data);
void  thread_write_float(uint32_t position, float data); 
void  thread_write_uint16_t(uint32_t position, uint16_t data); 
void  thread_write_uint32_t(uint32_t position, uint32_t data);*/



  /* Context switch**/
  t1=micros();
  thread_yield();
  t2=micros();
  t2=t2-t1;
  Serial.print("yield()\t");    
  Serial.println(t2); 
  delay(1000); 
   while(1){};
  /*
   The tasks accesses to the information
  */
//  th1=periodic_thread_create(&periodic_task1, NULL, NULL, 200, 30, 0, 1000000, 1000000, 500000, &error_handler_task1); 
  threads_subsystem_start();


}

.data
espaco: .asciiz " "
novalinha: .asciiz "\n"
entrada: .asciiz "\nInsira  #  : "
saida: .asciiz "\nLinha  # : "
matriz1: .word
.space 500
matriz2: .word
.space 500
matriz3: .word
.space 5000
.text


main:
   
   li $t9, 4 
  	
   la  $a0, matriz1          
   jal matriz_insere            
   
   la  $a0, matriz2           
   jal matriz_insere             
   
   
   la  $a2, matriz1           
   la  $a1, matriz2           
   la  $a0, matriz3           
   jal matriz_multiplica        
   
   
   la  $a0, matriz3           
   jal matriz_saida           
   
   li $v0, 10                  
   syscall     
                   
matriz_insere:
   li   $t0, 0                
   la   $s0, entrada       
   move $s1, $a0       
           
matriz_constroi:

   beq $t0, $t9, matriz_fim             
   addi $t0, $t0, 1            
   addi $t1, $t0, 48           
   sb $t1, 11($s0)             
   la $a0, entrada          
   li $v0, 4                   
   syscall                    

   li $t2,0
   
matriz_constroi_loop:
   li $v0, 12                  
   syscall                     
   
   subi $v0, $v0, 48           
   sb $v0, 0($s1)              
   
   la $a0, espaco              
   li $v0, 4                   
   syscall                     
   
   addi $s1, $s1, 4  
   addi $t2, $t2, 1 

   beq $t2, $t9, matriz_constroi  
   j matriz_constroi_loop


matriz_saida:
   li   $t0, 0                
   la   $s0, saida        
   move $s1, $a0   
              
matriz_imprime:
    beq $t0, $t9, matriz_fim          
   
   addi $t0, $t0, 1            
   addi $t1, $t0, 48           
   sb $t1, 5($s0)              
   
   la $a0, saida      
   li $v0, 4                   
   syscall                     

   li $t2, 0
   
matriz_imprime_loop:
   lb $a0, 0($s1)              
   li $v0, 1                   
   syscall                     
   
   la $a0, espaco               
   li $v0, 4                   
   syscall                     
   
   addi $s1, $s1, 4
   addi $t2, $t2, 1

   beq $t2, $t9, matriz_imprime    
   j matriz_imprime_loop


matriz_fim:
   la $a0, novalinha            
   li $v0, 4                   
   syscall                     
   
   jr $ra                      

matriz_multiplica:
 
      li $t2, 0
      li $t0, 0
      li $t3, 2

      add $t1, $zero $t9  
      li $s0, 0   
L1:   li $s1, 0   
L2:   li $s2, 0   


      mul $t2, $s0, $t1 

      add  $t2, $t2, $s1   
      sll  $t2, $t2, 3      
      
      div $t2, $t2, $t3


      add $t2, $a0, $t2   
      lb   $s4, 0($t2)      


L3:   mul $t0, $s2, $t1     
      add $t0, $t0, $s1  
      sll $t0, $t0, 3      

      div $t0, $t0, $t3

      add $t0, $a2, $t0   
      lb $s6, 0($t0)    

      mul  $t0, $s0, $t1  
      add $t0, $t0, $s2 
      sll  $t0, $t0, 3  

      div $t0, $t0, $t3
      add $t0, $a1, $t0  
      lb   $s7, 0($t0) 

      mul  $s6, $s7, $s6  
      add  $s4, $s4, $s6 

      addi  $s2, $s2, 1   
      bne   $s2, $t1, L3  
      sb    $s4, 0($t2)   

      addi  $s1, $s1, 1   
      bne    $s1, $t1, L2  
      addi  $s0, $s0, 1   
      bne    $s0, $t1, L1  

   j matriz_fim            

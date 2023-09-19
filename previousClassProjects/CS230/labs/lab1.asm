# lab1.asm
# This program will ask for an integer input for a size of an array.
# After this size is provided, the program will ask for N more integer
# inputs. Once this is provided, the program will sort the array of integers
# into ascending order, and will output the newly sorted array and the 
# median value.
# Landon Boone - CS 230
# 10-03-22


.data
space: .asciz " "
intCount: .asciz "How many values? "
intMedian: .asciz "Median = "

.text

main:
	addi sp, sp, -16
	li a7, 4
	la a0, intCount
	ecall
	li a7, 5
	ecall
	
	sw a0, 0(sp)
	
	call addElement 
	
	
	addi  sp, sp, 16
	
	

addElement: #adds element of size provided 
	li t0, 0 #i = 0;
	lw a0, 0(sp) #grabs size of array
	mv t2, a0 # sets t2 into size
	addElementStart: #While i is less than the size, elements are inputted
		beq t0, t2, addElementEnd
		li a7, 5 
		ecall
		
		slli t3, t0, 2 #offset * size
		add t3, sp, t3 #base + offset * size
		sw a0, (t3) # stores value to "arr[i]"
		
		addi t0, t0, 1 # i++
		j addElementStart
	addElementEnd: 
		j sortFunct

sortFunct: # bubblesorts the array in ascending order. Heavily utilized
	   # bubblesort provided by Dr. Marz in notes.

	doSortFunctStart:
		li t0, 1 # i = 1
		li t1, 0 # check value for ending the sort function
		forSortFunctStart:
			beq t0, t2, doSortFunctEnd #if i < size, continues "forLoop"
			slli t3, t0, 2
			add t3, sp, t3
			
			lw t4, -4(t3) #grabs arr[i-1] and arr[i]
			lw t6, 0(t3)
		
			ble t4, t6, forSortFunctEnd # if arr[i-1] is less than/equal to
			# arr[i], the array values will not be swapped
			addi t1, zero, 1
			sw t4, 0(t3) #swaps arr[i] and arr[i=1]
			sw t6, -4(t3)
			
		forSortFunctEnd:
			addi t0, t0, 1 #i++
			j forSortFunctStart
	
	doSortFunctEnd:
		bne t1, zero, doSortFunctStart
		j printNew
		
printNew : #function to print the newly sorted array
	li t0, 1
	addi t5, t2, 1
		printStart:
			beq t0, t5, printEnd
			slli t3, t0, 2
			add t3, sp, t3
			
			lw a0, -4(t3)
			li a7, 1
			ecall
		
			li a7, 4
			la a0, space
			ecall
		
			addi t0, t0, 1
			j printStart
	printEnd:
		j medianFunct
medianFunct: # finds the median value.
	li t1, 1
	li t6, 2 
	rem t5, t2, t6
	div t4, t2, t6
	li t0, 0
	beqz t5, medFunctEvenStart
	beq t5, t1, medFunctOddStart
			
		medFunctOddStart: #if the size is odd, the median will be middle value
			beq t0, t4, medFunctOddEnd
			slli t3, t0, 2
			add t3, sp, t3
			lw a0, 4(t3)
			mv t1, a0
			addi t0, t0, 1
			j medFunctOddStart
		medFunctOddEnd:
			la a0, intMedian
			ecall	
			
			mv a0, t1
			li a7, 4
			li a7, 1
			ecall
			j done 
		medFunctEvenStart: # if the size is even, the median will be the average
		# of the two middle values rounded down.
			beq t0, t4, medFunctEvenEnd
			slli t3, t0, 2
			add t3, sp, t3
			lw a0, 0(t3)
			mv t1, a0
			lw a0, 4(t3)
			mv t5, a0
			addi t0, t0, 1
			j medFunctEvenStart
		medFunctEvenEnd: 
			la a0, intMedian
			ecall	
			
			add t3, t5, t1
			divw  t4, t3, t6
			
			mv a0, t4
			li a7, 4
			li a7, 1
			ecall
			j done
		done:
			li t6, 1
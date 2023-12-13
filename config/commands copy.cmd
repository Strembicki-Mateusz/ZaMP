#define ROTATE_SPEED 10

/*
* Przykładowy zestaw poleceń
*/

Begin_Parallel_Actions
    Set Podstawa1 0 0 0 0 0 0
    Set Podstawa1.Ramie1 0 0.5 0 0 0 0
    Set Podstawa1.Ramie1.Ramie2 0 4 0 0 0 0
End_Parallel_Actions

Begin_Parallel_Actions
Move Podstawa1 3 3
End_Parallel_Actions

Begin_Parallel_Actions
    Rotate Podstawa1 OY ROTATE_SPEED 180 
End_Parallel_Actions

Begin_Parallel_Actions
Move Podstawa1 3 3
End_Parallel_Actions
Begin_Parallel_Actions
    Pause 1000
End_Parallel_Actions
Begin_Parallel_Actions
    Rotate Podstawa1 OX ROTATE_SPEED 360 
End_Parallel_Actions
Begin_Parallel_Actions
    Rotate Podstawa1 OY ROTATE_SPEED 360 
End_Parallel_Actions
Begin_Parallel_Actions
    Rotate Podstawa1 OZ ROTATE_SPEED 360 
End_Parallel_Actions
Begin_Parallel_Actions
    Pause 1000
End_Parallel_Actions
Begin_Parallel_Actions
Move Podstawa1 3 3
Move Podstawa1.Ramie1 3 3 
Move Podstawa1.Ramie1.Ramie2 3 4 
Rotate Podstawa1 OX ROTATE_SPEED 360 
Rotate Podstawa1.Ramie1 OY ROTATE_SPEED 720 
Rotate Podstawa1.Ramie1.Ramie2 OZ ROTATE_SPEED 1080 
End_Parallel_Actions
Begin_Parallel_Actions
    Move Podstawa1 1 5
    Move Podstawa1.Ramie1 2 10
    Move Podstawa1.Ramie1.Ramie2 3 15
End_Parallel_Actions
#define ROTATE_SPEED 10

/*
* Przykładowy zestaw poleceń
*/

Begin_Parallel_Actions
    Set Base 0 0 0 0 0 0
    Set Base.Hood 0 0 0 0 0 0
    Set Base.Hood.Wheel 0 0 0 0 0 0
    Set Base.Wheel 0 0 0 0 0 0
End_Parallel_Actions
Begin_Parallel_Actions
    Rotate Base OZ ROTATE_SPEED 90 
    Rotate Base OX ROTATE_SPEED 180 
    Rotate Base OY ROTATE_SPEED 360 
    Rotate Base.Wheel OZ ROTATE_SPEED 180 
    Rotate Base.Hood.Wheel OZ ROTATE_SPEED 180 
End_Parallel_Actions
Begin_Parallel_Actions
    Rotate Base.Wheel OZ 7 10080 
    Rotate Base.Hood.Wheel OZ 30 10080 
End_Parallel_Actions

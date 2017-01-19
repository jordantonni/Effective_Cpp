/*
 * Declare data members private
 * 
 * 
 * Provide access to them via a functional interface:
 * - Keeping all access to data members as functions provides consistency
 * - Can define w,rw,r,no access to members via functions
 * - Encapsulation
 *      - Easily replace access to a variable through a function with a computation instead
 *      - Alert other areas that a value has changed (e.g. observer pattern)
 *      - Easily maintain class invariants by enforcing values
 *     
 * Protected is just as bad as public
 *  - Public means you are not free to modify them due to breaking the coupling with the client
 *  - Protected means the same thing as you now break the inherited classes, in turn breaking the client
 * 
 */

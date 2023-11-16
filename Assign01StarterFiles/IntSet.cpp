// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     compile-time array whose size is IntSet::MAX_SIZE;
//     the member variable data references the array.
// (2) The distinct int value with earliest membership is stored
//     in data[0], the distinct int value with the 2nd-earliest
//     membership is stored in data[1], and so on.
//     Note: No "prior membership" information is tracked; i.e.,
//           if an int value that was previously a member (but its
//           earlier membership ended due to removal) becomes a
//           member again, the timing of its membership (relative
//           to other existing members) is the same as if that int
//           value was never a member before.
//     Note: Re-introduction of an int value that is already an
//           existing member (such as through the add operation)
//           has no effect on the "membership timing" of that int
//           value.
// (4) The # of distinct int values the IntSet currently contains
//     is stored in the member variable used.
// (5) Except when the IntSet is empty (used == 0), ALL elements
//     of data from data[0] until data[used - 1] contain relevant
//     distinct int values; i.e., all relevant distinct int values
//     appear together (no "holes" among them) starting from the
//     beginning of the data array.
// (6) We DON'T care what is stored in any of the array elements
//     from data[used] through data[IntSet::MAX_SIZE - 1].
//     Note: This applies also when the IntSet is empry (used == 0)
//           in which case we DON'T care what is stored in any of
//           the data array elements.
//     Note: A distinct int value in the IntSet can be any of the
//           values an int can represent (from the most negative
//           through 0 to the most positive), so there is no
//           particular int value that can be used to indicate an
//           irrelevant value. But there's no need for such an
//           "indicator value" since all relevant distinct int
//           values appear together starting from the beginning of
//           the data array and used (if properly initialized and
//           maintained) should tell which elements of the data
//           array are actually relevant.

#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;

IntSet::IntSet() : used(0){} //Default constructor

int IntSet::size() const
{
   //Returns the number in used which is the number
   //of elements in the array.
   return used;
}

bool IntSet::isEmpty() const
{
   //If used is 0 then no elemnts are in
   //the array meaning its empty.
   if(used == 0){
      return true;
   }
   return false;
}

bool IntSet::contains(int anInt) const
{
   //Checks if the array is empty or not.
   //If empty returns false.
   if(used > 0){
      for(int i = 0; i < used; i++ ){
         if(data[i] == anInt){ //Checks if anInt is a value of the array.
            return true;
         }
      }
   }
   return false;
}

bool IntSet::isSubsetOf(const IntSet& otherIntSet) const
{
   //Checks if the invoking IntSet is empty.
   if(otherIntSet.isEmpty()){
      return true;
   }
   
   //Element is set equal to the value in the spot of index.
   for(int i = 0; i < used; i++){
      int element = data[i];
      bool found = false;
      
      //Element is compared to see if it matches a value in otherIntSet.
      //If a matching element is found, found is set to true and the for
      //loop ends to get the next value from the IntSet to contiune the
      //process until there are no more values left.
      for(int j = 0; j < otherIntSet.used; j++){
         if(element == otherIntSet.data[j]){
            found = true;
            break;
         }
      }
      //If a matching value is not found return false.
      if(!found){
         return false;
      }
   }
   return true;
}

void IntSet::DumpData(ostream& out) const
{  // already implemented ... DON'T change anything
   if (used > 0)
   {
      out << data[0];
      for (int i = 1; i < used; ++i)
         out << "  " << data[i];
   }
}

IntSet IntSet::unionWith(const IntSet& otherIntSet) const
{
   //Checks that the size will be under MAX_SIZE.
   assert(size() + (otherIntSet.subtract(*this)).size() <= MAX_SIZE);
       
   //Creates a copy of the invoking IntSet.
   IntSet unionSet = (*this);
       
   for(int i = 0; i < otherIntSet.used; i++){
      if(!unionSet.contains(otherIntSet.data[i])){
         unionSet.add(otherIntSet.data[i]);
      }
    }
   return unionSet;
}

IntSet IntSet::intersect(const IntSet& otherIntSet) const
{
   //Creates a copy of the invoking IntSet.
   IntSet intersectSet = (*this);
    
   //Iterates thru both arrays and finds any matching elements.
   //If the elements match they are put into intersectSet.
   for(int i = 0; i < intersectSet.used; i++){  //SIMPLIFY AND FIX--
      for(int j = 0; j < otherIntSet.used; j++){  //----------------
         if(!intersectSet.contains(otherIntSet.data[i])){  //-------
            intersectSet.remove(otherIntSet.data[i]);  //-----------
         }
      }
   }
   return intersectSet;
}

IntSet IntSet::subtract(const IntSet& otherIntSet) const
{
   //Creates a copy of the invoking IntSet.
   IntSet subtractSet = (*this);
    
   //If subtractSet contains the same element as otherIntSet
   //the the element is removed from the set.
   for(int i = 0; i < otherIntSet.used; i++){
      if(subtractSet.contains(otherIntSet.data[i])){
         subtractSet.remove(otherIntSet.data[i]);
      }
   }
   return subtractSet;
}

void IntSet::reset()
{
   //Sets used to 0 to ignore the current elements in the invoking
   //IntSet and "reset" the invoking IntSet.
   used = 0;
}

bool IntSet::add(int anInt)
{
   //Checks if we are under MAX_SIZE and that theres no duplicate elements.
   assert(contains(anInt) ? size() <= MAX_SIZE : size() < MAX_SIZE);
    
   //Checks if anInt is already an element in IntSet.
   //If false then anInt is added to IntSet.
   if(contains(anInt) == false){
      data[used] = anInt;
      used++;
      return true;
   }
   return false;
}

bool IntSet::remove(int anInt)
{
   //Checks is anInt is an element of IntSet.
   //If it is in IntSet then the element is found and removed.
   if(contains(anInt) == true){
      for(int i = 0; i < used; i++ ){
         if (data[i] == anInt){
            for(int j = i; j < used - 1; j++){
               data[j] = data[j+1];
            }
            used--;
            return true;
         }
      }
   }
   return false;
}

bool equal(const IntSet& is1, const IntSet& is2) //fix
{
   //If is1 is a subset of is2 AND if is2 is a subset of
   //is1 then they must be equal and return true.
   if(is1.isSubsetOf(is2) && is2.isSubsetOf(is1)){
      return true;
   }
   return false;
}

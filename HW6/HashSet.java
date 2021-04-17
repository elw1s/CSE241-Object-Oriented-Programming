/** 
 * HashSet Class
 * 
 * @author ArdaKılıc 
 * 
 * */ 

import java.util.ConcurrentModificationException;

@SuppressWarnings("unchecked")
public class HashSet<E> implements Set<E> {
    //Holds elements of HashSet
    private E[] arr_Hash;
    //Holds number of elements in HashSet
    private int size_Set;
    //Modification Counter
    private int modCount = 0;

    /**
     * @param size is size of HashSet
     * @throws IllegalArgumentException
     */
    public HashSet(int size) throws IllegalArgumentException{
        if(size < 0) throw new IllegalArgumentException();
        arr_Hash = (E[]) new Object[size];
    }
    /**
     * Constructs the HashSet with default value (1).
     */
    public HashSet(){
        this(1);
    }
    /**
     * 
     * @param size New size of HashSet
     */
    private void setSize(int size){
        size_Set = size;
    }
    /**
    Returns the number of elements in this collection
     * @return number of elements
     */
    public int size(){
        return size_Set;
    }
    /**
    Returns an iterator over the collection
     * @return Iterator Reference
     */
    public Iterator<E> iterator(){
        return new Itr();
    }
    /**
     * 
     * @param e Element that will be checked 
     * @return True when there is an element same as parameter. Otherwise false will be returned
     */
    private boolean isDuplicated(E e){
        for(int i = 0; i < size(); i++){
            if(e == arr_Hash[i]) return true;
        }
        return false;
    }
    /**
    Ensures that this collection contains the specified element
     * @param e A Generic Value
     * @return True when operation is succeed.
     */
    public boolean add(E e){
        if(isDuplicated(e)) return false;
        modCount++;
        if(size() == arr_Hash.length){
            increaseCapacity(1);
        }
        arr_Hash[size()] = e;
        setSize(1+size_Set);
        return true;
    }
    /**
    Increases the capacity
     * @param size value to increase the capacity of HashSet
     * @throws IllegalArgumentException
     */
    public void increaseCapacity(int size) throws IllegalArgumentException{
        if(size < 0) throw new IllegalArgumentException();
        E[] temp = (E[]) new Object[size + arr_Hash.length];
            for(int i=0; i < arr_Hash.length; i++){
                temp[i] = arr_Hash[i];
            }
        arr_Hash = temp;
    }
    /**
    Adds all of the elements in the specified collection to this
collection
     *@param c Generic Collection
     *@return True when operation is succeed.
     * 
     */
    public boolean addAll(Collection<E> c){
        Iterator<E> iter = c.iterator();
        int size = c.size();
        if(arr_Hash.length < c.size()+size()){
            increaseCapacity(c.size()+size() - arr_Hash.length);
        }
        for(int i = size(); i < arr_Hash.length; i++){
            iter.next();
            if(isDuplicated(iter.getElement())){
                i--;
                size --;
            }
            else arr_Hash[i] = iter.getElement();
        }
        setSize(size()+size);
        modCount++;
        if(size == 0) return true;
        else return false;
    }
    /**
     * Clears the HashSet
     */
    public void clear(){
        arr_Hash = null;
    }
    /**
    Returns true if this collection contains the specified element.
     * @param e Generic Value
     * @return True when parameter is in HashSet, otherwise false.
     * 
     */
    public boolean contains(E e){
        for(int i = 0; i < size(); i++){
            if(e == arr_Hash[i]) return true;
        }
        return false;
    }  
    /**
     * Returns true if this collection contains all of the elements in the
specified collection.
        @param e Generic Collection
     * @return True when all values of parameter are in HashSet, otherwise false.
     * 
     */
    public boolean containsAll(Collection<E> c){
        int num = c.size();
        Iterator<E> iter = c.iterator();
        while(iter.hasNext()){
            iter.next();
            for(int i = 0; i < size(); i++){
                if(arr_Hash[i] == iter.getElement()){
                    num --;
                }   
            }
        }
        if(num == 0) return true;
        else return false;

    }
    /**
     * @return true when HashSet is empty
     */
    public boolean isEmpty(){
        return size() == 0;
    }
    /**
     * 
     * @param index This will be deleted index.
     * @param newSize New size of the HashSet (size - 1)
     */    
    private void copyArr(int index , int newSize) throws IllegalArgumentException{
        if(index < 0 || newSize < 0) throw new IllegalArgumentException();
        E[] temp = (E[]) new Object[newSize];  
        for(int i = 0 ; i < index; i++){
            temp[i] = arr_Hash[i];
        }
        
        for(int i = index; i < size()-1; i++){
            temp[i] = arr_Hash[i+1]; 
        }
        arr_Hash = temp;
    }

    /**Prints HashSet's elements within brackets*/
    public void print(){
        Iterator<E> iter = this.iterator();
        System.out.print("[");
        while(iter.hasNext()){
            System.out.print(iter.next());
            if(iter.hasNext()) System.out.print(",");
        }
        System.out.println("]");
    }
    /**
     * @param e Generic Value
     * @return True when remove operation is succeed. Otherwise it will be false
     */
    public boolean remove(E e){
        if(contains(e)){
            for(int i = 0; i < size(); i++){
                if(e == arr_Hash[i]) {
                    copyArr(i,size()-1);
                    setSize(size()-1);
                    modCount++;
                    return true;
                }
            }
        }
        return false;
    } 
    /**
     * @param c Generic Collection
     * @return True when all operation is succeed.
     */
    public boolean removeAll(Collection<E> c){
        Iterator<E> iter = c.iterator();
        while(iter.hasNext()){
            iter.next();
            for(int i = 0; i < size(); i++){
                if(arr_Hash[i] == iter.getElement()){
                   remove(arr_Hash[i]);    
                }   
            }
        }  
            modCount++;
            return true;
    }
     /**
     * @param c Generic Collection
     * @return True when all operation is succeed
     */
    public boolean retainAll(Collection<E> c){
        for(int i = 0; i < size(); i++){
            boolean hasFound = false;
            Iterator<E> iter = c.iterator();
            while(iter.hasNext()){
                if(iter.next() == arr_Hash[i]){
                    hasFound = true;
                    break;
                }
            }
            if(!hasFound){
                remove(arr_Hash[i]);
                i--;
            }
        }
        modCount++;
        return true;
    }
    /**
     * Inner class of HashSet.
     */
    public class Itr implements Iterator<E> {
        //Next index
        private int next;
        //Last Returned index
        private int lastReturned = -1;
        //Expected Modification Counter
        private int expectedModCount = modCount;
        /**
         * @return True if there's next element.
         */
        public boolean hasNext(){
            return size() != next;
        }
        /**
         * @return The element that iterator points to
         * @throws IndexOutOfBoundsException
         */
        public E getElement() throws IndexOutOfBoundsException{
            if(lastReturned == -1) throw new IndexOutOfBoundsException();
            return arr_Hash[lastReturned];
        }
        /**
         * @return The element that iterator points to
         * @throws IndexOutOfBoundsException
         */
        public E next() throws IndexOutOfBoundsException{
            isChanged();
            if(next >= size()) 
             throw new IndexOutOfBoundsException();

            lastReturned = next;
            next ++;
            return arr_Hash[lastReturned];
         }
         /**
          * @throws IndexOutOfBoundsException
          */
        public void remove() throws IndexOutOfBoundsException{
            isChanged();
            if(lastReturned == -1) throw new IndexOutOfBoundsException();
            arr_Hash[lastReturned] = null;
            next--;
            lastReturned = -1;
            expectedModCount = modCount;
            setSize(size()-1);
         }
        /**
         * To checked that is there any change on HashSet without using iterator.
         * @throws ConcurrentModificationException
         */
        public void isChanged() throws ConcurrentModificationException{
            if(modCount != expectedModCount) throw new ConcurrentModificationException();
         }

      
      } 

   
}

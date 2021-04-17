/** 
 * LinkedList Class
 * 
 * @author ArdaKılıc 
 * 
 * */ 

import java.util.ConcurrentModificationException;
import java.util.NoSuchElementException;

@SuppressWarnings("unchecked")
public class LinkedList<E> implements List<E>, Queue<E> {
    //Holds elements of LinkedList
    private E[] arr_Linked;
    //Holds number of elements in LinkedList
    private int size_List;
    //Modification Counter
    private int modCount = 0;

    /**
     * Returns last element of LinkedList
     * @return Last element of LinkedList
     * @throws OutOfMemoryError
     */
    public E getLast() throws OutOfMemoryError{
        if(arr_Linked.length < 0) throw new OutOfMemoryError();
        return arr_Linked[size()-1];
    }
    /**
     * Returns first element of LinkedList
     * @return first element of LinkedList
     * @throws OutOfMemoryError
     */
    public E getFirst() throws OutOfMemoryError{
        if(arr_Linked.length < 0) throw new OutOfMemoryError(); 
        return arr_Linked[0];
    }
    /**
     * Inserts the specified element into this queue
     * @param e Generic Value
     * @return True when operation is succeed
     * @throws OutOfMemoryError
     */
    public boolean offer(E e) throws OutOfMemoryError{
        if(size() < 0) throw new OutOfMemoryError();
        else if(size() == arr_Linked.length){
            increaseCapacity(1);
        }
        arr_Linked[size()] = e;
        setSize(1+size_List);
        modCount++;
        return true;
    }
    /**
     * Retrieves, but does not remove, the head of this queue.
     * @return first element of LinkedList
     */
    public E element(){
        return getFirst();
    }

    /**
     * Retrieves and removes the head of this queue, or throws if this queue is empty.
     * @return first element of LinkedList before removing
     * @throws NoSuchElementException
     */
    public E poll() throws NoSuchElementException{
        if(arr_Linked.length == 0) throw new NoSuchElementException();
        E firstElement = arr_Linked[0];
        E[] temp = (E[]) new Object[arr_Linked.length-1];    
        for(int i = 0; i < arr_Linked.length-1; i++){
            temp[i] = arr_Linked[i+1];
        }
        arr_Linked = temp;
        setSize(size()-1);
        return firstElement;
    }
    /**
     * @param size is size of LinkedList
     * @throws IllegalArgumentException
     */
    public LinkedList(int size) throws IllegalArgumentException{
        if(size < 0) throw new IllegalArgumentException();
        arr_Linked = (E[]) new Object[size];
    }
    /**
     * Constructs the LinkedList with default value (1).
     */
    public LinkedList(){
        this(1);
    }
    /**
     * 
     * @param size New size of LinkedList
     */
    private void setSize(int size){
        size_List = size;
    }
    /**
    Returns the number of elements in this collection
     * @return number of elements
     */
    public int size(){
        return size_List;
    }
    /**
    Returns an iterator over the collection
     * @return Iterator Reference
     */
    public Iterator<E> iterator(){
        return new Itr();
    }
    /**
    Ensures that this collection contains the specified element
     * @param e A Generic Value
     * @return True when operation is succeed.
     * @throws OutOfMemoryError
     */
    public boolean add(E e) throws OutOfMemoryError{
        if(size() < 0) throw new OutOfMemoryError();
        if(size() == arr_Linked.length){
            increaseCapacity(1);
        }
        arr_Linked[size()] = e;
        setSize(1+size_List);
        modCount++;
        return true;
    }
    /**
    Increases the capacity
     * @param size value to increase the capacity of LinkedList
     * @throws IllegalArgumentException
     */
    public void increaseCapacity(int size) throws IllegalArgumentException{
        if(size < 0) throw new IllegalArgumentException();
        E[] temp = (E[]) new Object[size + arr_Linked.length];
            for(int i=0; i < arr_Linked.length; i++){
                temp[i] = arr_Linked[i];
            }
        arr_Linked = temp;
    }
    /**
    Adds all of the elements in the specified collection to this
collection
     *@param c Generic Collection
     *@return True when operation is succeed.
     * 
     */
    public boolean addAll(Collection<E> c){
    try{
        Iterator<E> iter = c.iterator();
        int size = c.size();
        if(arr_Linked.length < c.size()+size()){
            increaseCapacity(c.size()+size() - arr_Linked.length);
        }
        for(int i = size(); i < arr_Linked.length; i++){
            iter.next();
            arr_Linked[i] = iter.getElement();
        }
        setSize(size()+size);
    }
    finally{
        modCount++;
    }
        return true;
    }
    /**
     * Clears the LinkedList
     */
    public void clear(){
        arr_Linked = null;
    }
    /**Prints LinkedList's elements within brackets*/
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
    Returns true if this collection contains the specified element.
     * @param e Generic Value
     * @return True when parameter is in LinkedList, otherwise false.
     * 
     */
    public boolean contains(E e){
        for(int i = 0; i < size(); i++){
            if(e == arr_Linked[i]) return true;
        }
        return false;
    }   
    /**
     * Random Access
     * @param index 
     * @return element at that index.
     */
    public E at(int index){
        return arr_Linked[index];
    }
    /**
    Returns true if this collection contains all of the elements in the
specified collection.
     * @param e Generic Collection
     * @return True when all values of parameter are in LinkedList, otherwise false.
     * 
     */
    public boolean containsAll(Collection<E> c){
        int num = c.size();
        Iterator<E> iter = c.iterator();
        while(iter.hasNext()){
        iter.next();
            for(int i = 0; i < size(); i++){
                if(arr_Linked[i] == iter.getElement()){
                    num --;
                }   
            }   
        }
        if(num == 0) return true;
        else return false;

    }
    /**
     * @return true when LinkedList is empty
     */
    public boolean isEmpty(){
        return size() == 0;
    }
     /**
     * 
     * @param index This will be deleted index.
     * @param newSize New size of the LinkedList (size - 1)
     * @throws IllegalArgumentException
     */       
    private void copyArr(int index , int newSize) throws IllegalArgumentException{
        if(index < 0 || newSize < 0) throw new IllegalArgumentException();

        E[] temp = (E[]) new Object[newSize]; 
        for(int i = 0 ; i < index; i++){
            temp[i] = arr_Linked[i];
        }
        for(int i = index; i < newSize; i++){
            temp[i] = arr_Linked[i+1]; 
        }
        arr_Linked = temp;
    }
    /**
     * @param e Generic Value
     * @return True when remove operation is succeed. Otherwise it will be false
     */    
    public boolean remove(E e){
        if(contains(e)){
            for(int i = 0; i < size(); i++){
                if(e == arr_Linked[i]) {
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
                if(arr_Linked[i] == iter.getElement()){
                    remove(arr_Linked[i]);
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
                if(iter.next() == arr_Linked[i]){
                    hasFound = true;
                    break;
                }
            }
            if(!hasFound){
                remove(arr_Linked[i]);
                i--;
            }
        }
        modCount++;
        return true;
    }

    /**
     * Inner class of LinkedList.
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
            return arr_Linked[lastReturned];
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
            return arr_Linked[lastReturned];
         }
         /**
          * Does not works with queue
          * @throws RuntimeException
          */
        public void remove() throws RuntimeException{
            throw new RuntimeException();
         }
        /**
         * To checked that is there any change on LinkedList without using iterator.
         * @throws ConcurrentModificationException
         */
        public void isChanged() throws ConcurrentModificationException{
            if(modCount != expectedModCount) throw new ConcurrentModificationException();
         }
      } 
}

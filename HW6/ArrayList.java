/** 
 * ArrayList Class
 * 
 * @author ArdaKılıc 
 * 
 * */ 

import java.util.ConcurrentModificationException;

@SuppressWarnings("unchecked")
public class ArrayList<E> implements List<E> {

    /**Holds elements of ArrayList*/
    private E[] arr_list;
    /**Holds number of elements in ArrayList*/
    private int size_List;
    /**Modification Counter*/
    private int modCount = 0;
    /**Prints ArrayList's elements within brackets*/
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
     * @param size is size of ArrayList
     * @throws IllegalArgumentException
     */
    public ArrayList(int size) throws IllegalArgumentException{
        if(size < 0) throw new IllegalArgumentException();
        arr_list = (E[]) new Object[size];
    }
    /**
     * Constructs the ArrayList with default value (1).
     */
    public ArrayList(){
        this(1);
    }
    /**
     * Random Access
     * @param index 
     * @return element at that index.
     */
    public E at(int index){
        return arr_list[index];
    }
    /**
     * 
     * @param size New size of ArrayList
     */
    private void setSize(int size){
        size_List = size;
    }
    /**
     * Returns the number of elements in this collection.
     * @return number of elements
     */
    public int size(){
        return size_List;
    }
    /**
     * Returns an iterator over the collection
     @return Iterator Reference
     */
    public Iterator<E> iterator(){
        return new Itr();
    }
    /**
    Ensures that this collection contains the specified element
     * @param e A Generic Value
     * @return True when operation is succeed.
     */
    public boolean add(E e){
        modCount++;
        if(size() == arr_list.length){
            increaseCapacity(1);
        }
        arr_list[size()] = e;
        setSize(1+size_List);
        return true;
    }
    /**
        Increases the capacity
     * @param size value to increase the capacity of ArrayList
     * @throws IllegalArgumentException
     */
    public void increaseCapacity(int size) throws IllegalArgumentException{
        if(size < 0) throw new IllegalArgumentException();

        E[] temp = (E[]) new Object[size + arr_list.length];
            for(int i=0; i < arr_list.length; i++){
                temp[i] = arr_list[i];
            }
        arr_list = temp;
    }
    /**
    Adds all of the elements in the specified collection to this
collection
     *@param c Generic Collection
     *@return True when operation is succeed.
     * 
     */
    public boolean addAll(Collection<E> c){ 
        modCount++;
        Iterator<E> iter = c.iterator();
        if(arr_list.length < c.size()+size()){
            increaseCapacity(c.size()+size() - arr_list.length);
        }
        for(int i = size(); i < arr_list.length; i++){
            iter.next();
            arr_list[i] = iter.getElement();
        }
        setSize(size()+c.size());
        return true;
    }
    /**
     * Clears the ArrayList
     */
    public void clear(){
        arr_list = null;
    }
    /**
    Returns true if this collection contains the specified element.
     * @param e Generic Value
     * @return True when parameter is in ArrayList, otherwise false.
     * 
     */
    public boolean contains(E e){
        for(int i = 0; i < size(); i++){
            if(e == arr_list[i]) return true;
        }
        return false;
    }   
    /**
    Returns true if this collection contains all of the elements in the
specified collection.
     * @param e Generic Collection
     * @return True when all values of parameter are in ArrayList, otherwise false.
     * 
     */
    public boolean containsAll(Collection<E> c){
        int num = c.size();
        Iterator<E> iter = c.iterator();
        while(iter.hasNext()){
            iter.next();
            for(int i = 0; i < size(); i++){
                if(arr_list[i] == iter.getElement()){
                    num --;
                }   
            }
        }
        if(num == 0) return true;
        else return false;

    }
    /**
     * @return true when ArrayList is empty
     */
    public boolean isEmpty(){
        return size() == 0;
    }
    /**
     * 
     * @param index This will be deleted index.
     * @param newSize New size of the ArrayList (size - 1)
     */
    private void copyArr(int index , int newSize){
        if(index < 0 || newSize < 0) throw new IllegalArgumentException();

        E[] temp = (E[]) new Object[newSize]; 
        
        for(int i = 0 ; i < index; i++){
            temp[i] = arr_list[i];
        }
        
        for(int i = index; i < newSize; i++){
            temp[i] = arr_list[i+1]; 
        }
        arr_list = temp;
    }
    /**
     * @param e Generic Value
     * @return True when remove operation is succeed. Otherwise it will be false
     */
    public boolean remove(E e){
        if(contains(e)){
            for(int i = 0; i < size(); i++){
                if(e == arr_list[i]) {
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
                if(arr_list[i] == iter.getElement()){
                    remove(arr_list[i]);
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
                if(iter.next() == arr_list[i]){
                    hasFound = true;
                    break;
                }
            }
            if(!hasFound){
                remove(arr_list[i]);
                i--;
            }
        }
        modCount++;
        return true;
    }

    /**
     * Inner class of ArrayList.
     */
    public class Itr implements Iterator<E> {
        /**Next index*/
        private int next;
        /**Last Returned index*/
        private int lastReturned = -1;
        /**Expected Modification Counter*/
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
            return arr_list[lastReturned];
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
            return arr_list[lastReturned];
         }
         /**
          * @throws IndexOutOfBoundsException
          */
        public void remove() throws IndexOutOfBoundsException{
            isChanged();
            if(lastReturned == -1) throw new IndexOutOfBoundsException();
            arr_list[lastReturned] = null;
            next--;
            lastReturned = -1;
            expectedModCount = modCount;
            setSize(size()-1);
         }
        /**
         * To checked that is there any change on ArrayList without using iterator.
         * @throws ConcurrentModificationException
         */
        public void isChanged() throws ConcurrentModificationException{
            if(modCount != expectedModCount) throw new ConcurrentModificationException();
         }

      
      } 

   
}

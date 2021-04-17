/** 
 * Iterator Interface for Itr classes
 * 
 * @author ArdaKılıc 
 * 
 * */ 
public interface Iterator<E>{
    /** Returns true if the iteration has more elements.*/
    public boolean hasNext();
    /** Returns the next element in the iteration and advances the
iterator. */
    public E next();
    /** Removes from the underlying collection the last element returned
by this iterator. This method does not work for Queues, it throws
an exception.*/
    public void remove();
    /** Returns the element which is pointed by iterator */
    public E getElement();
    /** Checks the modifications without iterator */
    public void isChanged();
}

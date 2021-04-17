/** 
 * Collection interface
 * 
 * @author ArdaKılıc 
 * 
 * */ 
public interface Collection<E> 
{
    /**Returns an iterator over the collection*/
    Iterator<E> iterator();
    /**Ensures that this collection contains the specified element*/
    boolean add(E e);
    /**Adds all of the elements in the specified collection to this collection*/
    boolean addAll(Collection<E> c);
    /**Removes all of the elements from this collection*/
    void clear();
    /**Returns true if this collection contains the specified element.*/
    boolean contains(E e);        
    /**Returns true if this collection contains all of the elements in the specified collection.*/
    boolean containsAll(Collection<E> c);
    /**Returns true if this collection contains no elements.*/
    boolean isEmpty(); 
    /**Removes a single instance of the specified element from this collection, if it is present */
    boolean remove(E e); 
    /**Removes all of this collection's elements that are also contained in the specified collection*/
    boolean removeAll(Collection<E> c);
    /**Retains only the elements in this collection that are contained in the specified collection */
    boolean retainAll(Collection<E> c);
    /**Returns the number of elements in this collection*/
    int size(); 
}

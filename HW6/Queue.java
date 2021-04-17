/** 
 * Queue interface
 * 
 * @author ArdaKılıc 
 * 
 * */
public interface Queue<E> extends Collection<E> 
{   
    /**Retrieves, but does not remove, the head of this queue. */
    E element(); 
    /**Inserts the specified element into this queue*/
    boolean offer(E e);
    /**Retrieves and removes the head of this queue, or throws if this queue is empty.*/
    E poll(); 
}

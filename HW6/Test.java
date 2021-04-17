public class Test{
    
    public void TestLinkedListString(){
        System.out.printf("\n\n\t\tLinkedList<String> arr\n\n");
        LinkedList<String> arr = new LinkedList<String>(5);
        /* Adding Values to the arr */
        arr.add("Apple");
        arr.add("Strawberry");
        arr.add("Orange");
        arr.add("Banana");
        arr.add("Grape");
        /* Printing arr */
        System.out.print("LinkedList<String> arr = ");
        arr.print();
        System.out.println("arr.size(): " + arr.size()); 
        System.out.println("arr.isEmpty(): " + arr.isEmpty()); 

        /* HashSet Collection for testing REMOVEALL function */
        HashSet<String> hash_remove = new HashSet<String>();
        hash_remove.add("Orange"); //Adding values to the hashSet
        hash_remove.add("Grape");
        arr.removeAll(hash_remove); //calling removeAll function
        System.out.print("Remove Orange and Grape from arr using removeAll(): ");
        arr.print();
        
        /* ArrayList Collection to test addAll() function  */
        ArrayList<String> arrStr = new ArrayList<String>();
        arrStr.add("Apricot");
        arrStr.add("Peach");
        arrStr.add("Lemon");
        arrStr.add("Pineapple");
        arr.addAll(arrStr);
        System.out.print("Add Apricot,Peach,Lemon,Pineapple to the arr using addAll(): ");
        arr.print();
        
        /* Testing other functions */
        System.out.println("Is there Peach in this array?: " + arr.contains("Peach"));
        System.out.println("Is there Watermelon in this array?: " + arr.contains("Watermelon"));
        System.out.println("First element of arr -> arr.element(): " + arr.element());
        
        /* HashSet Collection to test containsAll() function */
        HashSet<String> hash = new HashSet<String>();
        hash.add("Coconut");
        hash.add("Lemon");
        hash.add("Pear");
        hash.add("Apple");
        /* HashSet Collection to test containsAll() function */
        HashSet<String> hash2 = new HashSet<String>();
        hash2.add("Apricot");
        hash2.add("Banana");
        /* Testing ContainsAll() function */
        System.out.println("Contains All [Coconut,Lemon,Pear,Apple]: " + arr.containsAll(hash));
        System.out.println("Contains All [Apricot,Banana]: " + arr.containsAll(hash2));
        /* Testing RetainAll() function */
        arr.retainAll(arrStr);
        System.out.print("After RetainAll [Apricot,Peach,Lemon,Pineapple] Operation: ");
        arr.print();
        /* Testing special functions of LinkedList */
        arr.offer("Fig");
        System.out.print("arr.offer(Fig): ");
        arr.print();
        System.out.println("arr.poll() returns: " + arr.poll());
        System.out.print("After arr.poll(): "); 
        arr.print();
    }

    public void TestLinkedListInteger(){
        System.out.printf("\n\n\t\tLinkedList<Integer> arr\n\n");
        LinkedList<Integer> arr = new LinkedList<Integer>(5);
        /* Adding Values to the arr */
        arr.add(Integer.valueOf(5));
        arr.add(Integer.valueOf(15));
        arr.add(Integer.valueOf(20));
        arr.add(Integer.valueOf(25));
        arr.add(Integer.valueOf(5));
        /* Printing arr */
        System.out.print("LinkedList<Integer> arr = ");
        arr.print();
        System.out.println("arr.size(): " + arr.size()); 
        System.out.println("arr.isEmpty(): " + arr.isEmpty()); 

        /* HashSet Collection for testing REMOVEALL function */
        HashSet<Integer> hash_remove = new HashSet<Integer>();
        hash_remove.add(Integer.valueOf(5)); //Adding values to the hashSet
        hash_remove.add(Integer.valueOf(12));
        arr.removeAll(hash_remove); //calling removeAll function
        System.out.print("Remove 5 and 12 from arr using removeAll(): ");
        arr.print();
        
        /* ArrayList Collection to test addAll() function  */
        ArrayList<Integer> arrInt = new ArrayList<Integer>();
        arrInt.add(Integer.valueOf(50));
        arrInt.add(Integer.valueOf(55));
        arrInt.add(Integer.valueOf(60));
        arrInt.add(Integer.valueOf(65));
        arr.addAll(arrInt);
        System.out.print("Add 50,55,60,65 to the arr using addAll(): ");
        arr.print();
        
        /* Testing other functions */
        System.out.println("Is there 55 in this array?: " + arr.contains(Integer.valueOf(55)));
        System.out.println("Is there 12 in this array?: " + arr.contains(Integer.valueOf(12)));
        System.out.println("First element of arr -> arr.element(): " + arr.element());
        
        /* HashSet Collection to test containsAll() function */
        HashSet<Integer> hash = new HashSet<Integer>();
        hash.add(Integer.valueOf(12));
        hash.add(Integer.valueOf(25));
        hash.add(Integer.valueOf(60));
        hash.add(Integer.valueOf(19));
        /* HashSet Collection to test containsAll() function */
        HashSet<Integer> hash2 = new HashSet<Integer>();
        hash2.add(Integer.valueOf(60));
        hash2.add(Integer.valueOf(25));
        /* Testing ContainsAll() function */
        System.out.println("Contains All [12,25,60,19]: " + arr.containsAll(hash));
        System.out.println("Contains All [25,60]: " + arr.containsAll(hash2));
        /* Testing RetainAll() function */
        System.out.print("After RetainAll [12,25,60,19] Operation: ");
        arr.print();
        /* Testing special functions of LinkedList */
        arr.offer(Integer.valueOf(38));
        System.out.print("arr.offer(38): ");
        arr.print();
        System.out.println("arr.poll() returns: " + arr.poll());
        System.out.print("After arr.poll(): "); 
        arr.print();
    }

    public void TestHashSetInteger(){
        System.out.printf("\n\n\t\tHashSet<Integer> arr\n\n");
        HashSet<Integer> arr = new HashSet<Integer>(5);
        /* Adding Values to the arr */
        arr.add(Integer.valueOf(1));
        arr.add(Integer.valueOf(3));
        arr.add(Integer.valueOf(5));
        /* Printing arr */
        System.out.print("HashSet<Integer> arr = ");
        arr.print();
        System.out.println("arr.size(): " + arr.size()); 
        System.out.println("arr.isEmpty(): " + arr.isEmpty()); 

        /* HashSet Collection for testing REMOVEALL function */
        HashSet<Integer> hash_remove = new HashSet<Integer>();
        hash_remove.add(Integer.valueOf(1)); //Adding values to the hashSet
        hash_remove.add(Integer.valueOf(5));
        arr.removeAll(hash_remove); //calling removeAll function
        System.out.print("Remove 1 and 5 from arr using removeAll(): ");
        arr.print();
        
        /* ArrayList Collection to test addAll() function  */
        ArrayList<Integer> arrInt = new ArrayList<Integer>();
        arrInt.add(Integer.valueOf(7));
        arrInt.add(Integer.valueOf(9));
        arrInt.add(Integer.valueOf(11));
        arrInt.add(Integer.valueOf(13));
        arr.addAll(arrInt);
        System.out.print("Add 7,9,11,13 to the arr using addAll(): ");
        arr.print();
        
        /* Testing other functions */
        System.out.println("Is there 3 in this array?: " + arr.contains(Integer.valueOf(55)));
        System.out.println("Is there 4 in this array?: " + arr.contains(Integer.valueOf(12)));
        
        /* HashSet Collection to test containsAll() function */
        HashSet<Integer> hash = new HashSet<Integer>();
        hash.add(Integer.valueOf(1));
        hash.add(Integer.valueOf(3));
        hash.add(Integer.valueOf(5));
        /* HashSet Collection to test containsAll() function */
        HashSet<Integer> hash2 = new HashSet<Integer>();
        hash2.add(Integer.valueOf(9));
        hash2.add(Integer.valueOf(3));
        /* Testing ContainsAll() function */
        System.out.println("Contains All [1,3,5]: " + arr.containsAll(hash));
        System.out.println("Contains All [9,3]: " + arr.containsAll(hash2));
        /* Testing RetainAll() function */
        System.out.print("After RetainAll [7,9,11,13] Operation: ");
        arr.print();
        /* Adding Duplicate Element to the arr */
        arr.add(Integer.valueOf(7));
        System.out.print("After adding 7 as a duplicate element: ");
        arr.print();
    }

    public void TestHashSetString(){
        System.out.printf("\n\n\t\tHashSet<String> arr\n\n");
        HashSet<String> arr = new HashSet<String>(5);
        /* Adding Values to the arr */
        arr.add("Alligator");
        arr.add("Dog");
        arr.add("Cat");
        arr.add("Monkey");
        arr.add("Lion");
        /* Printing arr */
        System.out.print("HashSet<String> arr = ");
        arr.print();
        System.out.println("arr.size(): " + arr.size()); 
        System.out.println("arr.isEmpty(): " + arr.isEmpty()); 

        /* HashSet Collection for testing REMOVEALL function */
        HashSet<String> hash_remove = new HashSet<String>();
        hash_remove.add("Dog"); //Adding values to the hashSet
        hash_remove.add("Lion");
        arr.removeAll(hash_remove); //calling removeAll function
        System.out.print("Remove Dog and Lion from arr using removeAll(): ");
        arr.print();
        
        /* ArrayList Collection to test addAll() function  */
        ArrayList<String> arrStr = new ArrayList<String>();
        arrStr.add("Sheep");
        arrStr.add("Camel");
        arrStr.add("Giraffe");
        arrStr.add("Duck");
        arr.addAll(arrStr);
        System.out.print("Add Sheep,Camel,Giraffe,Duck to the arr using addAll(): ");
        arr.print();
        
        /* Testing other functions */
        System.out.println("Is there Camel in this array?: " + arr.contains("Camel"));
        System.out.println("Is there Dog in this array?: " + arr.contains("Dog"));
        
        /* HashSet Collection to test containsAll() function */
        HashSet<String> hash = new HashSet<String>();
        hash.add("Sheep");
        hash.add("Duck");
        hash.add("Monkey");
        hash.add("Cat");
        /* HashSet Collection to test containsAll() function */
        HashSet<String> hash2 = new HashSet<String>();
        hash2.add("Snake");
        hash2.add("Fox");
        /* Testing ContainsAll() function */
        System.out.println("Contains All [Sheep,Duck,Monkey,Cat]: " + arr.containsAll(hash));
        System.out.println("Contains All [Snake,Fox]: " + arr.containsAll(hash2));
        /* Testing RetainAll() function */
        arr.retainAll(arrStr);
        System.out.print("After RetainAll [Sheep,Camel,Giraffe,Duck] Operation: ");
        arr.print();
        /* Adding Duplicate Element to the arr */
        arr.add("Camel");
        System.out.print("After adding the Camel as a duplicate element: ");
        arr.print();
    }

    public void TestArrayListString(){
        System.out.printf("\n\n\t\tArrayList<String> arr\n\n");
        ArrayList<String> arr = new ArrayList<String>(5);
        /* Adding Values to the arr */
        arr.add("JavaScript");
        arr.add("HTML");
        arr.add("SQL");
        arr.add("Python");
        /* Printing arr */
        System.out.print("ArrayList<String> arr = ");
        arr.print();
        System.out.println("arr.size(): " + arr.size()); 
        System.out.println("arr.isEmpty(): " + arr.isEmpty()); 

        /* HashSet Collection for testing REMOVEALL function */
        HashSet<String> hash_remove = new HashSet<String>();
        hash_remove.add("SQL"); //Adding values to the hashSet
        hash_remove.add("HTML");
        arr.removeAll(hash_remove); //calling removeAll function
        System.out.print("Remove SQL and HTML from arr using removeAll(): ");
        arr.print();
        
        /* ArrayList Collection to test addAll() function  */
        ArrayList<String> arrStr = new ArrayList<String>();
        arrStr.add("Java");
        arrStr.add("C");
        arrStr.add("Go");
        arrStr.add("C++");
        arr.addAll(arrStr);
        System.out.print("Add Java,C,Go,C++ to the arr using addAll(): ");
        arr.print();
        
        /* Testing other functions */
        System.out.println("Is there 'Go' in this array?: " + arr.contains("Go"));
        System.out.println("Is there Swift in this array?: " + arr.contains("Swift"));
        
        /* HashSet Collection to test containsAll() function */
        HashSet<String> hash = new HashSet<String>();
        hash.add("Kotlin");
        hash.add("Rust");
        hash.add("Perl");
        hash.add("JavaScript");
        /* HashSet Collection to test containsAll() function */
        HashSet<String> hash2 = new HashSet<String>();
        hash2.add("C++");
        hash2.add("Java");
        /* Testing ContainsAll() function */
        System.out.println("Contains All [Kotlin,Rust,Perl,JavaScript]: " + arr.containsAll(hash));
        System.out.println("Contains All [C++,Java]: " + arr.containsAll(hash2));
        /* Testing RetainAll() function */
        arr.retainAll(arrStr);
        System.out.print("After RetainAll [Java,C++,Go,C] Operation: ");
        arr.print();
        /* Adding Duplicate Element to the arr */
        arr.add("Go");
        System.out.print("After adding the Go as a duplicate element: ");
        arr.print();
    }

    public void TestArrayListInteger(){
        System.out.printf("\n\n\t\tArrayList<Integer> arr\n\n");
        ArrayList<Integer> arr = new ArrayList<Integer>(5);
        /* Adding Values to the arr */
        arr.add(Integer.valueOf(0));
        arr.add(Integer.valueOf(2));
        arr.add(Integer.valueOf(4));
        arr.add(Integer.valueOf(6));
        arr.add(Integer.valueOf(8));
        /* Printing arr */
        System.out.print("ArrayList<Integer> arr = ");
        arr.print();
        System.out.println("arr.size(): " + arr.size()); 
        System.out.println("arr.isEmpty(): " + arr.isEmpty()); 

        /* HashSet Collection for testing REMOVEALL function */
        HashSet<Integer> hash_remove = new HashSet<Integer>();
        hash_remove.add(Integer.valueOf(4)); //Adding values to the hashSet
        hash_remove.add(Integer.valueOf(10));
        arr.removeAll(hash_remove); //calling removeAll function
        System.out.print("Remove 4 and 10 from arr using removeAll(): ");
        arr.print();
        
        /* ArrayList Collection to test addAll() function  */
        ArrayList<Integer> arrInt = new ArrayList<Integer>();
        arrInt.add(Integer.valueOf(10));
        arrInt.add(Integer.valueOf(12));
        arrInt.add(Integer.valueOf(14));
        arrInt.add(Integer.valueOf(16));
        arr.addAll(arrInt);
        System.out.print("Add 10,12,14,16 to the arr using addAll(): ");
        arr.print();
        
        /* Testing other functions */
        System.out.println("Is there 3 in this array?: " + arr.contains(Integer.valueOf(55)));
        System.out.println("Is there 12 in this array?: " + arr.contains(Integer.valueOf(12)));
        
        /* HashSet Collection to test containsAll() function */
        HashSet<Integer> hash = new HashSet<Integer>();
        hash.add(Integer.valueOf(12));
        hash.add(Integer.valueOf(5));
        hash.add(Integer.valueOf(8));
        hash.add(Integer.valueOf(4));
        /* HashSet Collection to test containsAll() function */
        HashSet<Integer> hash2 = new HashSet<Integer>();
        hash2.add(Integer.valueOf(2));
        hash2.add(Integer.valueOf(10));
        /* Testing ContainsAll() function */
        System.out.println("Contains All [12,5,8,4]: " + arr.containsAll(hash));
        System.out.println("Contains All [2,10]: " + arr.containsAll(hash2));
        /* Testing RetainAll() function */
        arr.retainAll(arrInt);
        System.out.print("After RetainAll [10,12,14,16] Operation: ");
        arr.print();
        /* Adding Duplicate Element to the arr */
        arr.add(Integer.valueOf(14));
        System.out.print("After adding 14 as a duplicate element: ");
        arr.print();
    }
    public static void main(String[] args){
        Test obj = new Test();
        System.out.print("\n***********************************************\n");
        obj.TestLinkedListInteger();
        System.out.print("\n***********************************************\n");
        obj.TestHashSetInteger();
        System.out.print("\n***********************************************\n");
        obj.TestArrayListInteger();
        System.out.print("\n***********************************************\n");
        obj.TestLinkedListString();
        System.out.print("\n***********************************************\n");
        obj.TestHashSetString();
        System.out.print("\n***********************************************\n");
        obj.TestArrayListString();
    }

}
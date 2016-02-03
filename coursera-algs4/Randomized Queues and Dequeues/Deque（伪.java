import java.util.Iterator;

public class Deque<Item> implements Iterable<Item> {
   private Item []stuff;
   private int L = 0,R = 0,S = 0;
   public Deque()                           // construct an empty deque
   {
       stuff =(Item []) new Object[2];
   }
   public boolean isEmpty()                 // is the deque empty?
   {
       return S == 0;
   }
   public int size()                        // return the number of items on the deque
   {
       return S;
   }
   public void addFirst(Item item)          // add the item to the front
   {
       if (L == -1) Lresize((int)(1.5*stuff.length));
       stuff[L--] = item;
       S++;

   }
   public void addLast(Item item)           // add the item to the end
   {
       if (R == stuff.length) Rresize((int)(1.5*stuff.length));
       stuff[R++] = item;
       S++;
   }   
   public Item removeFirst()                // remove and return the item from the front
   {
       Item item = stuff[++L];
       stuff[L] = null;
       if (L < stuff.length - 1 && L == (3*stuff.length)/8) Lresize((3*stuff.length)/4);
       S--;
       return item;
      
   }
   public Item removeLast()                 // remove and return the item from the end
   {
       Item item = stuff[--R];
       stuff[R] = null;
       if (R > 0 && R == (5*stuff.length)/8) Rresize((3*stuff.length)/4);
       S--;
       return item; 
       
   }
   public Iterator<Item> iterator()         // return an iterator over items in order from front to end
   {
       return new ReverseArrayIterator();
   }

   
   
   private class ReverseArrayIterator implements Iterator<Item>{
       private int i = L;
       public boolean hasNext() { return i != R-1; }
       public Item next() { return stuff[++i]; }
       public void remove() { /* not supported */ }
   }
   
   private void Rresize(int capacity)
   {
       Item[] copy = (Item []) new Object[capacity];
       for(int i = 0 ; i < R ; i++)
           copy[i] = stuff[i];
       stuff = copy;
   }
   private void Lresize(int capacity)
   {
       Item[] copy =(Item []) new Object[capacity];
       for(int i = stuff.length - 1;i >= L;i--)
           copy[capacity - stuff.length +i] = stuff[i];
       stuff = copy;
   }
} 
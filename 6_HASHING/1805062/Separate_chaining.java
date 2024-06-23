import java.util.*;

public  class Separate_chaining {
    static class HashNode {
        String key;
        int value;

        HashNode next;

        public HashNode(String key, int value) {
            this.key = key;
            this.value = value;
        }
    }

    private ArrayList<HashNode> hashTab;
    private int capacity;//array's capacity
    private int current_size;//curr_size

    public Separate_chaining(int cap) {
        this.capacity = cap;
        hashTab = new ArrayList<>();
        for (int i = 0; i < capacity; i++)
            hashTab.add(null);
    }

    int hash1(String key, int m) {
        long p = 137;
        int h = 0;
        for (int i = 0; i < key.length(); i++) {
            char c = key.charAt(i);
            h = (int) ((h * p + c) % m);
        }
        return h;
    }

    int hash2(String key, int m) {
        long p = 0x811C9DC5 % m;
        int h = 0;
        for (int i = 0; i < key.length(); i++) {
            char c = key.charAt(i);
            h = (int) ((h * p) ^ c) % m;
        }
        return h;
    }

    public int Search(String key,int num) {
        int index;
        if(num==1)
            index = hash1(key, capacity);
        else index = hash2(key, capacity);
        HashNode cur = hashTab.get(index);
        int count=1;
        while (cur != null) {
            if (cur.key.equals(key))
                return count;
            cur = cur.next;
            count++;
        }
        return count;
    }

    public int add(String key, int value,int num) {
        int index;
        if(num==1)
            index = hash1(key, capacity);
        else index = hash2(key, capacity);
        if(index<0) index *=-1;
        HashNode head = hashTab.get(index);
        int count = 0;
        while (head != null) {
            if (head.key.equals(key)) {
                return count;
            }
            head = head.next;
            count++;
        }

        head = hashTab.get(index);
        HashNode newNode = new HashNode(key, value);
        newNode.next = head;
        hashTab.set(index, newNode);
        return count;
    }

    public HashNode remove(String key,int num) {
        int index;
        if(num==1)
            index = hash1(key, capacity);
        else index = hash2(key, capacity);

        HashNode head_chain = hashTab.get(index);

        HashNode prev = null;
        while (head_chain != null) {
            if (head_chain.key.equals(key))
                break;
            prev = head_chain;
            head_chain = head_chain.next;
        }

        if (head_chain == null)
            return null;//doesn't exist

        current_size--;

        if (prev != null)
            prev.next = head_chain.next;
        else
            hashTab.set(index, head_chain.next);

        return head_chain;
    }

    static Vector<String> gen(int n, int len){
        Set<String> ret = new HashSet<String>();
        String sb;
        String chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijk"
                +"lmnopqrstuvwxyz";
        Random r = new Random();
        while(ret.size() < n){

            int i = 0;
            StringBuilder s = new StringBuilder();
            while(i< len)
            {
                s.append(chars.charAt(r.nextInt(chars.length())));

                i++;
            }
            sb = String.valueOf(s);
            ret.add(sb);
        }

        Vector<String> v = new Vector<String>();
        for(String x : ret)v.add(x);
        return v;
    }
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        System.out.println("The size of table: ");
        int num = sc.nextInt();
        System.out.println("Press 1 to apply hash1 and any other for hash2");
        int hash = sc.nextInt();
        Random rand = new Random(System.currentTimeMillis());
        Random r = new Random();
        Separate_chaining ht = new Separate_chaining(num);
        Vector<String>strings = gen(10000, 7);
        int collision =0;

        double Average_Probes = 0;
        for(int i = 0; i < strings.size(); i++)
        {
            collision += ht.add(strings.get(i), i + 1,hash);
        }
        for(int i = 0; i < 1000; i++)
        {
            int l = (r.nextInt() % strings.size() + strings.size()) % strings.size();
            Average_Probes += ht.Search(strings.get(l),hash);
        }

        Average_Probes /= 1000;
        if(hash==1) {
            System.out.println("Collision for hash1 " + collision);
            System.out.println("Average Probes for hash1" + " " + Average_Probes);
        }
        if(hash!=1) {
            System.out.println("Collision for hash2   " + collision);
            System.out.println("Average Probes for hash2" + " " + Average_Probes);
        }

    }
}

import java.util.*;

public class DoubleHashing {
    static class HashNode {
        String key;
        int value;

        HashNode(String key, int value) {
            this.key = key;
            this.value = value;
        }
    }

    static class HashTable {

        private int capacity;

        private ArrayList<HashNode> hashTab;

        public HashTable(int cap)
        {
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
            long p = 0x811C9DC5L % m;
            int h = 0;
            for (int i = 0; i < key.length(); i++) {
                char c = key.charAt(i);
                h = (int) ((h * p) ^ c) % m;
            }
            return h;
        }

        int auxHash(String key, int m) {
            long h = 0, a = 2, b = 3;
            long t;
            for (int i = 0; i < key.length(); i++) {
                char c = key.charAt(i);
                h =  (h * a + c) % m;
                a = (a + b) % m;
                t = a;
                a = b;
                b = t;
            }
            return (int)h;
        }

        public int Search(String key,int num) {
            int hash1;
            if(num==1)
                hash1 = hash1(key, capacity);
            else hash1 = hash2(key, capacity);


            int hash2 = auxHash(key, capacity);

            for (int i = hash1, j = 0; j < capacity; j++, i = (i + hash2) % capacity) {
                HashNode head = hashTab.get(i);
                if (head == null) continue;
                if (head.key == key) {
                    return j+1;

                }
            }
            return capacity+1;
        }


        public int insert(String key, int value,int num) {

            int hash1;
            if(num==1)
                hash1 = hash1(key, capacity);
            else hash1 = hash2(key, capacity);
            if(hash1<0) hash1 *=-1;
            int hash2 = auxHash(key, capacity);
            for (int i = hash1, j = 0; j < capacity; j++, i = (i + hash2) % capacity) {
                HashNode head = hashTab.get(i);
                if (head == null) {
                    hashTab.set(i, new HashNode(key, value));
                    return j;
                }
            }
            return capacity;
        }


        public HashNode remove(String key,int num) {
            int hash1;
            if(num==1)
                hash1 = hash1(key, capacity);
            else hash1 = hash2(key, capacity);
            if(hash1<0) hash1 *=-1;
            int hash2 = auxHash(key, capacity);
            for (int i = hash1, j = 0; j < capacity; j++, i = (i + hash2) % capacity) {
                HashNode head = hashTab.get(i);
                if (head == null) continue;
                if (head.key == key) {
                    hashTab.set(i, null);
                    return head;

                }
            }
            return null;
        }
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
        int n = sc.nextInt();

        Random rand = new Random(System.currentTimeMillis());
        Random r = new Random();
        HashTable ht = new HashTable(num);
        Vector<String>strings = gen(10000, 7);
        int collision =0;

        double Average_Probes = 0;
        for(int i = 0; i < strings.size(); i++)
        {
            collision += ht.insert(strings.get(i), i + 1,n);
        }
        for(int i = 0; i < 1000; i++)
        {
            int l = (r.nextInt() % strings.size() + strings.size()) % strings.size();
            Average_Probes += ht.Search(strings.get(l),n);
        }

        Average_Probes /= 1000;
        if(n==1) {
            System.out.println("Collision for hash1 " + collision);
            System.out.println("Average Probes for hash1" + " " + Average_Probes);
        }
        if(n!=1) {
            System.out.println("Collision for hash2   " + collision);
            System.out.println("Average Probes for hash2" + " " + Average_Probes);
        }

    }
}

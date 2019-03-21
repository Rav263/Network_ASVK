import java.util.*;
import java.net.*;

public class Client {
    static int PORT_NUM = 2917;
    
    public static void main(String[] args) throws Exception {
        if (args.length < 1) {
            System.out.println("NO IP " + args.length);
            return;
        }

        System.out.print("Creating socket.. ");
        Socket server = new Socket(args[0], PORT_NUM);
        System.out.println("Successfull");

    }
}


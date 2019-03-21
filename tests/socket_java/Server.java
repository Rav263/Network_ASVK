import java.io.*;
import java.util.*;
import java.net.*;


public class Server {
    public static void main(String[] args) throws Exception{
        System.out.print("Creating socket.. ");
        ServerSocket server = new ServerSocket(2917);
        System.out.println("Successfull");

        System.out.print("Waiting for client.. ");
        Socket client = server.accept();

        System.out.println("Accepted");
    }
}

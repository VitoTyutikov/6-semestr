package vitaly;

import java.util.Random;
import java.util.regex.Pattern;

public class Main {
    public static void main(String[] args) {
        taskOne();
        taskTwo();
        taskThree();
    }

    public static void taskOne() {
        System.out.println("TASK 1: ");
        String regex = "^(-?(0,[0-9]*(\\(\\d*\\)|[1-9])|[1-9][0-9]*,[0-9]*(\\(\\d*\\)|[1-9])|[1-9][0-9]*)|0)?$";

        String[] numbers = {"0", "-6", "-0,5", "0,0(64)", " -0", "+2", "001", "0,(35)1", "-3,750"};

        for (String number : numbers) {

            if (number.matches(regex)) {
                System.out.println("Number " + number + " is valid");
            } else {
                System.out.println("Number " + number + " is invalid");
            }
        }

    }

    public static void taskTwo() {
        System.out.println("TASK 2");
        String[] codes = {"010101", "11", "00", "101", "010", "0110", "001", "1010", "0101", "1101"};
//        Pattern  regex = Pattern.compile("^(0+|1+|(10)+1?|(01)+0?)$");
        Pattern regex = Pattern.compile("^(0+|1+|(01)*0*|(10)*1*)$");
        for (String code : codes) {
            if (regex.matcher(code).matches()) {
                System.out.println(code + " is a valid binary code.");
            } else {
                System.out.println(code + " is an invalid binary code.");
            }
        }
    }
    public static void taskThree(){
        Random random = new Random();
        Pattern pattern = Pattern.compile("^-?\\d*[02468]$");
        //заканчивается либо на 0 или 2 или 4 или 6 или 8
        int count = 0;
        int evenCount = 0;

        while (evenCount < 10) {
            int num = random.nextInt(Integer.MAX_VALUE);
            String strNum = Integer.toString(num);

            if (pattern.matcher(strNum).matches()) {
                evenCount++;

                if (evenCount < 10) {
                    System.out.println(evenCount + ": " + num);
                }
            }

            count++;
        }

        System.out.println("Всего: " + count);
    }

}
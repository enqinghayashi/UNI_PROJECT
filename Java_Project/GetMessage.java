import java.io.*;
import java.util.*;

class Result {

    public static List<String> getMessageStatus(List<Integer> timestamps, List<String> messages, int k) {
        Map<String, Integer> lastDelivered = new HashMap<>();
        List<String> result = new ArrayList<>();

        for (int i = 0; i < timestamps.size(); i++) {
            int timestamp = timestamps.get(i);
            String message = messages.get(i);

            System.out.println("Processing message: " + message + " at timestamp: " + timestamp);

            if (lastDelivered.containsKey(message)) {
                int lastTime = lastDelivered.get(message);
                int timeDifference = timestamp - lastTime;

                System.out.println("Last delivered at: " + lastTime + ", Time difference: " + timeDifference);

                if (timeDifference < k) {
                    result.add("false");
                    System.out.println("Message dropped");
                } else {
                    result.add("true");
                    lastDelivered.put(message, timestamp);
                    System.out.println("Message delivered");
                }
            } else {
                result.add("true");
                lastDelivered.put(message, timestamp);
                System.out.println("Message delivered");
            }
        }

        return result;
    }
}

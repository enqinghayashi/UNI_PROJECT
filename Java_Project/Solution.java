
import java.io.*;
import java.util.*;
import java.util.stream.*;

class Result {

    public static List<String> getMessageStatus(List<Integer> timestamps, List<String> messages, int k) {
        Map<String, Integer> lastDelivered = new HashMap<>();
        List<String> result = new ArrayList<>();

        for (int i = 0; i < timestamps.size(); i++) {
            int timestamp = timestamps.get(i);
            String message = messages.get(i);

            if (lastDelivered.containsKey(message)) {
                int lastTime = lastDelivered.get(message);
                int timeDifference = timestamp - lastTime;

                if (timeDifference <= k) {
                    result.add("false");
                } else {
                    result.add("true");
                    lastDelivered.put(message, timestamp);
                }
            } else {
                result.add("true");
                lastDelivered.put(message, timestamp);
            }
        }

        return result;
    }
}

public class Solution {

    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int timestampsCount = Integer.parseInt(bufferedReader.readLine().trim());
        List<Integer> timestamps = IntStream.range(0, timestampsCount)
            .mapToObj(i -> {
                try {
                    return bufferedReader.readLine().replaceAll("\\s+$", "");
                } catch (IOException ex) {
                    throw new RuntimeException(ex);
                }
            })
            .map(String::trim)
            .map(Integer::parseInt)
            .collect(Collectors.toList());

        int messagesCount = Integer.parseInt(bufferedReader.readLine().trim());
        List<String> messages = IntStream.range(0, messagesCount)
            .mapToObj(i -> {
                try {
                    return bufferedReader.readLine();
                } catch (IOException ex) {
                    throw new RuntimeException(ex);
                }
            })
            .collect(Collectors.toList());

        int k = Integer.parseInt(bufferedReader.readLine().trim());

        List<String> result = Result.getMessageStatus(timestamps, messages, k);

        bufferedWriter.write(result.stream().collect(Collectors.joining("\n")) + "\n");

        bufferedReader.close();
        bufferedWriter.close();
    }
}

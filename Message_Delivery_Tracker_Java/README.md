# Timestamp-based Message Delivery Filter

## 📖 Project Description
This Java application implements a message filtering system that determines whether incoming messages should be delivered or dropped. The decision-making process is based on the timestamps of the messages and a configurable delay threshold, denoted as `k`. The primary goal is to prevent the processing of outdated or redundant messages by ensuring that only timely messages are passed through. This project demonstrates the use of Java collections (like `HashMap`) for efficient state tracking and conditional logic for implementing the filtering rules.

---

## ✨ Key Features
-   **Timestamp-based Filtering**: Messages are evaluated based on their arrival time.
-   **Configurable Delay Threshold (`k`)**: Allows customization of the time window for message validity.
-   **Duplicate/Outdated Message Prevention**: Drops messages that arrive too late relative to previous messages from the same source or a global window.
-   **Stateful Tracking**: Maintains a history of last delivery times for message sources to make informed decisions.
-   **Boolean Output**: Returns a list indicating "true" (deliver) or "false" (drop) for each processed message.

---

## ⚙️ Technologies Used
-   **Language**: Java (e.g., Java 8 or higher)
-   **Core Libraries**: Java Standard Library (Collections Framework, specifically `HashMap`)
-   **Build Tool (Optional)**: Maven or Gradle could be used for more complex setups, but not strictly necessary for a simple implementation.
-   **IDE**: Any Java-compatible IDE (e.g., IntelliJ IDEA, Eclipse, VS Code with Java extensions).

---

## 🚀 Setup and Usage

### 1. Prerequisites
-   Java Development Kit (JDK) installed (e.g., JDK 8 or newer).
-   Ensure your `JAVA_HOME` environment variable is set and the JDK's `bin` directory is in your system's PATH.

### 2. Compilation
Navigate to the `Message_Delivery_Tracker_Java` directory (or the current project directory) in your terminal. If your project has a simple structure (e.g., a single `.java` file or a few files in the default package):
```bash
javac YourMainClass.java # Replace YourMainClass.java with your main Java file name
```
If using a build tool like Maven:
```bash
mvn compile
```
Or Gradle:
```bash
gradle build
```

### 3. Running the Application
After successful compilation:
```bash
java YourMainClass # Replace YourMainClass with the name of your main class
```
If using a build tool, they often have specific commands to run the application:
Maven:
```bash
mvn exec:java -Dexec.mainClass="com.example.YourMainClass" # Adjust main class path
```
Gradle:
```bash
gradle run
```
The application might take input (e.g., message timestamps, delay threshold `k`) via command-line arguments, file input, or interactive prompts, depending on its design.

---

## 📝 Example Scenario
Consider a scenario where `k = 10` seconds.
- Message A (source S1) arrives at T=5. Delivered. Last delivery for S1 is T=5.
- Message B (source S2) arrives at T=7. Delivered. Last delivery for S2 is T=7.
- Message C (source S1) arrives at T=12. (12 < 5+10). Delivered. Last delivery for S1 is T=12.
- Message D (source S1) arrives at T=25. (25 >= 12+10). Delivered. Last delivery for S1 is T=25.
- Message E (source S2) arrives at T=15. (15 < 7+10). Delivered. Last delivery for S2 is T=15.

*(The exact logic for "source" and how `k` is applied might vary based on the specific implementation details of the project.)*

---

## 📄 License
This project is licensed under the MIT License. See the main [LICENSE](../../LICENSE) file for details.

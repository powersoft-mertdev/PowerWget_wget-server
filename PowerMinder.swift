import SwiftUI
import UserNotifications

struct Reminder: Identifiable, Codable {
    var id = UUID()
    var title: String
    var date: Date
}

class ReminderViewModel: ObservableObject {
    @Published var reminders: [Reminder] = [] {
        didSet {
            saveReminders()
        }
    }
    
    init() {
        loadReminders()
    }
    
    func addReminder(title: String, date: Date) {
        let newReminder = Reminder(title: title, date: date)
        reminders.append(newReminder)
        scheduleNotification(for: newReminder)
    }
    
    func scheduleNotification(for reminder: Reminder) {
        let content = UNMutableNotificationContent()
        content.title = "PowerMinder"
        content.body = reminder.title
        content.sound = .default
        
        let trigger = UNCalendarNotificationTrigger(dateMatching: Calendar.current.dateComponents([.year, .month, .day, .hour, .minute], from: reminder.date), repeats: false)
        let request = UNNotificationRequest(identifier: reminder.id.uuidString, content: content, trigger: trigger)
        
        UNUserNotificationCenter.current().add(request)
    }
    
    func saveReminders() {
        if let encoded = try? JSONEncoder().encode(reminders) {
            UserDefaults.standard.set(encoded, forKey: "reminders")
        }
    }
    
    func loadReminders() {
        if let data = UserDefaults.standard.data(forKey: "reminders"), let decoded = try? JSONDecoder().decode([Reminder].self, from: data) {
            reminders = decoded
        }
    }
}

struct ContentView: View {
    @StateObject private var viewModel = ReminderViewModel()
    @State private var title: String = ""
    @State private var date: Date = Date()
    
    var body: some View {
        NavigationView {
            VStack {
                TextField("Reminder Title", text: $title)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .padding()
                
                DatePicker("Select Date & Time", selection: $date, displayedComponents: [.date, .hourAndMinute])
                    .padding()
                
                Button("Add Reminder") {
                    viewModel.addReminder(title: title, date: date)
                    title = ""
                }
                .padding()
                .background(Color.blue)
                .foregroundColor(.white)
                .cornerRadius(10)
                
                List(viewModel.reminders) { reminder in
                    VStack(alignment: .leading) {
                        Text(reminder.title).font(.headline)
                        Text("Due: \(reminder.date, style: .date) \(reminder.date, style: .time)")
                            .font(.subheadline)
                            .foregroundColor(.gray)
                    }
                }
            }
            .navigationTitle("PowerMinder")
            .onAppear {
                UNUserNotificationCenter.current().requestAuthorization(options: [.alert, .sound, .badge]) { success, error in
                    if success {
                        print("Notifications allowed")
                    } else if let error = error {
                        print("Error: \(error.localizedDescription)")
                    }
                }
            }
        }
    }
}




import SwiftUI

@main
struct MyApp: App {
    var body: some Scene {
        WindowGroup {
            ContentView()
        }
    }
}

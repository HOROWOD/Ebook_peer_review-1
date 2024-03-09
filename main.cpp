#include <exception>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class EbookManager {
public:
	EbookManager()
		: ids_and_current_pages_(MAX_USER_COUNT_ + 1, -1),
		pages_and_users_count_(MAX_PAGE_COUNT_ + 1, 0)
	{
	}

	void ReadUserIdAndPage(int user_id, int current_page) {
		int last_page = ids_and_current_pages_[user_id];
		ids_and_current_pages_[user_id] = current_page;
		UpdateUsersCount(last_page, current_page);
	}

	void CheerUser(int user_id) {
		if (int current_user_page = ids_and_current_pages_[user_id]; current_user_page != -1) {
			int users_count_on_page = pages_and_users_count_[current_user_page];
			int count_of_users = GetUsersCount();
			if (count_of_users == 1) {
				std::cout << 1.0;
				return;
			}
			std::cout << (count_of_users - users_count_on_page) / static_cast<double>(count_of_users - 1);
		}
		else {
			std::cout << 0.0;
		}
}

private:
	static const int MAX_USER_COUNT_ = 100'000;
	static const int MAX_PAGE_COUNT_ = 1'000'000;

	int count_of_users_ = 0;
	std::vector<int> ids_and_current_pages_;
	std::vector<int> pages_and_users_count_;

	int GetUsersCount() {
		return pages_and_users_count_[0];
	}

	void UpdateUsersCount(int last_page, int current_page) {
		for (int i = last_page + 1; i <= current_page; ++i) {
			++pages_and_users_count_[i];
		}
	}
};

int main() {
	int request_count;
	std::cin >> request_count;
    std::cout << std::setprecision(6);

	EbookManager manager;
	for (int i = 0; i < request_count; ++i) {
		std::string request_id;
		std::cin >> request_id;
		if (request_id == "READ") {
			int user_id, page;
			std::cin >> user_id >> page;
			manager.ReadUserIdAndPage(user_id, page);
		}
		else if(request_id == "CHEER") {
			int user_id;
			std::cin >> user_id;
			manager.CheerUser(user_id);
            std::cout << (i < (request_count - 1) ? "\n" : "");
		}
	}
}
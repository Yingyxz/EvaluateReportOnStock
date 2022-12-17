#include "Transaction.h"
#include <iomanip>                                                                              

namespace fre {
    double Transaction::getOpen() const { return open; }
    double Transaction::getHigh() const { return high; }
    double Transaction::getLow() const { return low; }
    double Transaction::getClose() const { return close; }
    int Transaction::getVolume() const { return volume; }
    string Transaction::getDate() const { return date; }
    double Transaction::getAdjusted_close() const { return adj_close; }

    // Overload cout for trade
    ostream& operator<<(ostream& out, const Transaction& transaction) {
        out << fixed << setprecision(2);
        out << setw(13) << transaction.date << "|";
        out << setw(10) << transaction.open << "|";
        out << setw(10) << transaction.high << "|";
        out << setw(10) << transaction.low << "|";
        out << setw(10) << transaction.close << "|";
        out << setw(10) << transaction.adj_close << "|";
        if (transaction.total_daily_ret != 0.0) {
            out << setw(15) << transaction.total_daily_ret << "|";
        }
        out << setw(15) << transaction.volume << endl;
        return out;
    }

}

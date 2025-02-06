import requests

def currency_converter():
    source_currency = input("What is the source of currency you want to convert from? (Example: USD, IDR, EUR): ").upper()
    money_amount = float(input("Enter the amount of money you want to convert: "))
    target_currency = input("What is the target of currency you want to convert to? (Example: USD, IDR, EUR): ").upper()

    try:
        api_key = "" # Insert API key from exchangerate-api.com
        url_link = f"https://v6.exchangerate-api.com/v6/{api_key}/latest/{source_currency}"
        responses = requests.get(url_link)
        response_data = responses.json()

        if responses.status_code != 200:
            print("An error occurred while fetching exchange rates. Please try again later.")
            return

        rates = response_data.get("conversion_rates", {})
        if not rates:
            print("Conversion rates are not available for the given source currency.")
            return

        if target_currency not in rates:
            print(f"Conversion rate data for currency {target_currency} is not available. Please try again.")
            return

        conversion_rate = rates[target_currency]
        final_amount = money_amount * conversion_rate

        print(f"{money_amount} {source_currency} is equal to {final_amount:.2f} {target_currency}")

    except Exception as e:
        print(f"An error occurred: {e}")


if __name__ == "__main__":
    currency_converter()
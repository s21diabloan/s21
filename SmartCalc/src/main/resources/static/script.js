function calculate() {
    const inputValue = document.getElementById('inputValue').value;
    const xValue = document.getElementById('xValue').value;

    fetch('/calc/calculate', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
        },
        body: `inputValue=${encodeURIComponent(inputValue)}&xValue=${encodeURIComponent(xValue)}`,
    })
        .then(response => response.text())
        .then(data => {
            document.getElementById('result').innerText = `${data}`;
            loadHistory(); // Автоматически загружаем историю
        })
        .catch(error => {
            document.getElementById('result').innerText = 'Error: ' + error;
        });
}


function calculateCredit() {
    const amount = document.getElementById('inputAmount').value;
    const term = document.getElementById('inputTerm').value;
    const termPeriod = document.getElementById('termPeriod').value;
    const interestRate = document.getElementById('inputInterestRate').value;
    const interestType = document.getElementById('interestType').value;

    // Конвертируем срок в месяцах
    const termInMonths = termPeriod === 'years' ? term * 12 : term;
    const type = interestType === 'annuity' ? 0 : 1;

    // Формируем данные для отправки
    const data = new URLSearchParams();
    data.append('amount', amount);
    data.append('months', termInMonths);
    data.append('rate', interestRate);
    data.append('type', type);

    fetch('/calc/credit', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
        },
        body: data.toString(),
    })
        .then(response => response.json())  // Ожидаем, что сервер вернет JSON
        .then(result => {
            // Обновляем интерфейс с результатами
            document.getElementById('resultFirstPayment').innerText = result.firstPayment.toFixed(2);
            document.getElementById('resultLastPayment').innerText = result.lastPayment.toFixed(2);
            document.getElementById('resultOverpayment').innerText = result.overpayment.toFixed(2);
            document.getElementById('resultTotal').innerText = result.total.toFixed(2);
        })
        .catch(error => {
            console.error('Error:', error);
            alert('An error occurred while calculating the credit.');
        });
}


function openChart() {
    const equation = document.getElementById('inputValue').value;
    const minX = parseFloat(document.getElementById('inputMinX').value) || -10;
    const maxX = parseFloat(document.getElementById('inputMaxX').value) || 10;
    const minY = parseFloat(document.getElementById('inputMinY').value) || -10;
    const maxY = parseFloat(document.getElementById('inputMaxY').value) || 10;


    fetch('/calc/chart', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ equation, minX, maxX }),
    })
        .then(response => response.json())
        .then(data => {
            // Открытие новой вкладки
            const chartWindow = window.open('/chart.html', '_blank', 'width=400,height=500');
            if (!chartWindow) {
                alert('Please allow pop-ups for this website.');
                return;
            }

            // Отправка данных в новую вкладку
            chartWindow.onload = () => {
                chartWindow.postMessage({ equation, minX, maxX, minY, maxY, data }, '*');
            };
            loadHistory();
        })
        .catch(error => {
            console.error('Error generating chart:', error);
        });
}



function addValue(value) {
    const inputValueInput = document.getElementById('inputValue');
    inputValueInput.value += value; // Добавляет значение к текущему тексту в поле
}

function clearInputs() {
    const inputValueInput = document.getElementById('inputValue');
    const xValueInput = document.getElementById('xValue'); // Получаем элемент xValue
    const resultDiv = document.getElementById('result');

    inputValueInput.value = ''; // Очищает поле ввода inputValue
    xValueInput.value = ''; // Очищает поле ввода xValue
    resultDiv.innerText = '0'; // Сбрасывает текст результата
}

function showInfo() {
    const infoWindow = window.open('/info.html', '_blank', 'width=800,height=600');
    if (!infoWindow) {
        alert('Please allow pop-ups for this website.');
    }
}


function loadHistory() {
    fetch('/calc/history', {
        method: 'GET',
    })
        .then(response => response.json())
        .then(data => {
            const historyDropdown = document.getElementById('historyDropdown');
            historyDropdown.innerHTML = `<option value="">Выберите выражение...</option>`; // Сбрасываем список
            data.forEach(item => {
                const option = document.createElement('option');
                option.value = item;
                option.textContent = item;
                historyDropdown.appendChild(option);
            });
        })
        .catch(error => {
            console.error('Error loading history:', error);
        });
}

function handleHistorySelection() {
    const historyDropdown = document.getElementById('historyDropdown');
    const selectedExpression = historyDropdown.value;

    if (selectedExpression) {
        document.getElementById('inputValue').value = selectedExpression;
    }
}



function clearHistory() {
    fetch('/calc/clearHistory', {
        method: 'POST'
    })
        .then(() => {
            // Очищаем текстовую область истории
            document.getElementById('history').innerText = '';

            // Очищаем содержимое выпадающего списка истории
            const historyDropdown = document.getElementById('historyDropdown');
            historyDropdown.innerHTML = '<option value="">Выберите выражение...</option>';
        })
        .catch(error => {
            console.error('Error clearing history:', error);
        });
}

window.onload = loadHistory;

// Функция добавления элемента в список депозитов
function addDeposit(amount) {
    const depositList = document.getElementById('depositList');
    const listItem = document.createElement('li');
    listItem.textContent = `Deposit: ${amount} units`;
    depositList.appendChild(listItem);
}

// Функция добавления элемента в список снятий
function addWithdrawal(amount) {
    const withdrawalList = document.getElementById('withdrawalList');
    const listItem = document.createElement('li');
    listItem.textContent = `Withdrawal: ${amount} units`;
    withdrawalList.appendChild(listItem);
}

// Пример вызова функций
function performTransaction() {
    const transactionSum = document.getElementById('transactionAmount').value;
    const transactionType = document.querySelector('input[name="transactionType"]:checked').value;

    if (transactionType === 'deposit') {
        addDeposit(transactionSum);
    } else if (transactionType === 'withdraw') {
        addWithdrawal(transactionSum);
    }

    // Дополнительные действия, например, обновление баланса, расчет процентов и т.д.
    console.log(`Performed ${transactionType} of ${transactionSum} units`);
}

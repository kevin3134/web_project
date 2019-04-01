// Sends a new request to update the to-do list
function getList() {
    $.ajax({
        url: "/time_management/get-list-json",
        dataType : "json",
        success: updateList
    });
}

function updateList(items) {
    // Removes the old to-do list items
    $("li").remove();
console.log("update");
    // Adds each new todo-list item to the list
    $(items).each(function() {
        $("#todo-list").append(
            "<li><button onclick='deleteItem("+this.pk+")'>X</button> " +
                    this.fields.process_name +
                    ' <span class="details">' +
                    "(id=" + this.pk +
                    ", username=" + this.fields.username +
                    ", type=" + this.fields.type +
                    ", ip_addr=" + this.fields.ip_addr +
                    ", update_time=" + this.fields.update_time +
                    ", create_time=" + this.fields.create_time +
                    ")" +
                    "</span></li>"
        );
    });
}

function sanitize(s) {
    // Be sure to replace ampersand first
    return s.replace(/&/g, '&amp;')
            .replace(/</g, '&lt;')
            .replace(/>/g, '&gt;')
            .replace(/"/g, '&quot;');
}

function displayError(message) {
    $("#error").html(message);
}

function getCSRFToken() {
    var cookies = document.cookie.split(";");
    for (var i = 0; i < cookies.length; i++) {
        c = cookies[i].trim();
        if (c.startsWith("csrftoken=")) {
            return c.substring("csrftoken=".length, c.length);
        }
    }
    return "unknown";
}

function addItem() {
    var itemTextElement = $("#item");
    var itemTextValue   = itemTextElement.val();
    var time = new Date();
    var itemdata = {"process_name":itemTextValue,
                    "update_time":time,
                    "create_time":time,
                    "type":"send by js",
                    "username":"webpage"};


    // Clear input box and old error message (if any)
    itemTextElement.val('');
    displayError('');

    $.ajax({
        url: "/time_management/add-item",
        type: "POST",
        data: "item="+JSON.stringify(itemdata)+"&csrfmiddlewaretoken="+getCSRFToken(),
        dataType : "json",
        success: function(response) {
            if (Array.isArray(response)) {
                updateList(response);
            } else {
                displayError(response.error);
            }
        }
    });
}

function deleteItem(id) {
    $.ajax({
        url: "/time_management/delete-item/"+id,
        type: "POST",
        data: "csrfmiddlewaretoken="+getCSRFToken(),
        dataType : "json",
        success: updateList
    });
}

// The index.html does not load the list, so we call getList()
// as soon as page is finished loading
window.onload = getList;

// causes list to be re-fetched every 5 seconds
window.setInterval(getList, 5000);

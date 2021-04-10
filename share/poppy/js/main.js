/*
 * Author: Rafael Schreiber (i16066)
 * Project: pop3client_29
 * File: main.js
 * Date: 08-04-2021
 */

const $ = require("jquery");
const {Empty,  MailPreviewRequest, SpecifiedMail} = require('./poppy_pb.js');
const {MailServiceClient} = require('./poppy_grpc_web_pb.js');

var mailService = new MailServiceClient('http://127.0.0.1:42961');
var headersMap = new Map();

function hash_string(s) {
    var hash = 0, i, chr;
    if (s.length === 0) return hash;
    for (i = 0; i < s.length; i++) {
        chr   = s.charCodeAt(i);
        hash  = ((hash << 5) - hash) + chr;
        hash |= 0; // Convert to 32bit integer
    }
    return hash;
}


function set_mailbox_info(){
    var request = new Empty();
    mailService.getMailBoxInfo(request, {}, (err, response) => {
        $("#account-name").text(response.getAccount());
        $("#email-count").text(response.getLength());
        $("#mailbox-size").text(response.getSize());
        sessionStorage.setItem("available-pages", Math.ceil(response.getLength() / 10).toString());
    });
    $("#available-pages").text(sessionStorage.getItem("available-pages"));
}


function prepend_table(uidl, mailid){
    var entryHeader = headersMap.get(uidl);
    if (sessionStorage.getItem(uidl) === null){
        var tableRowHtml = `<tr id="${hash_string(uidl)}" uidl="${uidl}">
                                <th scope="row">${mailid}</th>
                                <td>${entryHeader.get("Subject")}</td>
                                <td>${entryHeader.get("From")}</td>
                                <td>${entryHeader.get("Date")}</td>
                                <td class="actions">
                                    <button onclick="ext.download_mail('${uidl}')" id="download-mail" type="button" class="btn btn-primary"><i class="fas fa-download"></i></button>
                                    <button onclick="ext.mark_mail_deleted('${uidl}')" id="delete-mail" type="button" class="btn btn-danger"><i class="fas fa-trash"></i></button>
                                </td>
                            </tr>`
    } else {
        var tableRowHtml = `<tr id="${uidl}" style="color: var(--ac-color)">
                                <th scope="row">${mailid}</th>
                                <td>${entryHeader.get("Subject")}</td>
                                <td>${entryHeader.get("From")}</td>
                                <td>${entryHeader.get("Date")}</td>
                                <td class="actions">
                                    <button onclick="ext.download_mail('${uidl}')" id="download-mail" type="button" class="btn btn-primary"><i class="fas fa-download"></i></button>
                                    <button id="delete-mail" type="button" class="btn btn-secondary"><i class="fas fa-trash"></i></button>
                                </td>
                            </tr>`
    }
    $("#table-body").append(tableRowHtml);
}


function set_mail_entries(page, entries=10) {
    var request = new MailPreviewRequest()
    request.setPos((page - 1) * entries);
    request.setLen(entries);
    $("#prev-link").hide();
    $("#next-link").hide();
    $("#loading-spinner").show();
    mailService.getMailPreviews(request, {}, (err, response) => {  
        response.getMailPreviewList().forEach( (item, index) => {
            if (sessionStorage.getItem("current-page") != 1) {
                $("#prev-link").show();
            }
            if (sessionStorage.getItem("current-page") !== sessionStorage.getItem("available-pages")) {
                $("#next-link").show();
            }
            $("#loading-spinner").hide();
            headersMap.set(item.getUidl(), item.getHeadersMap());  
            prepend_table(item.getUidl(), item.getMailid());
        });   
    });
}


function refresh_view(){
    $("#table-body").empty();
    $("#current-page").text(sessionStorage.getItem("current-page"));
    set_mailbox_info();
    set_mail_entries(sessionStorage.getItem("current-page"));
}


function next_page(){
    var currentPage = parseInt(sessionStorage.getItem("current-page"));
    if (currentPage != sessionStorage.getItem("available-pages")) {
        currentPage++;
        sessionStorage.setItem("current-page", currentPage.toString());
        refresh_view();
    }
}


function prev_page() {
    var currentPage = parseInt(sessionStorage.getItem("current-page"));
    if (currentPage > 1) {
        currentPage--;
        sessionStorage.setItem("current-page", currentPage.toString());
        refresh_view();
    }
}


function mark_mail_deleted(uidl) {
    if (sessionStorage.getItem(uidl) === null){
        var request = new SpecifiedMail();
        request.setUidl(uidl);
        mailService.deleteMail(request, {}, (err, response) => {
            if (response.getSuccess()){
                sessionStorage.setItem(uidl, "marked_for_deletion");
                $("#" + hash_string(uidl)).children("td.actions").children("#delete-mail").removeAttr("onclick");
                $("#" + hash_string(uidl)).children("td.actions").children("#delete-mail").removeClass("btn-danger");
                $("#" + hash_string(uidl)).children("td.actions").children("#delete-mail").addClass("btn-secondary");
                $("#" + hash_string(uidl)).css("color", "#D51B21");
            }
        });
    }
}


function reset_trash(){
    var request = new Empty();
    mailService.resetMailbox(request, {}, (err, response) => {
        if (response.getSuccess()){
            var currentPage = sessionStorage.getItem("current-page");
            var availablePages = sessionStorage.getItem("available-pages");
            sessionStorage.clear()
            sessionStorage.setItem("current-page", currentPage);
            sessionStorage.setItem("available-pages", availablePages);
            refresh_view();
        }
    });
}


function update_mailbox() {
    var request = new Empty();
    mailService.updateMailbox(request, {}, (err, response) => {
        if (response.getSuccess()){
            sessionStorage.setItem("current-page", "1");
            refresh_view();
        }
    });
}


function download_mail(uidl) {
    var request = new SpecifiedMail();
    mailService.downloadMail(request, {}, (err, response) => {
        if (response.getSuccess()){
            var blob = new Blob([response.getMailcontent()], { type: "message/rfc822" });
            var a = document.createElement('a');
            a.download = headersMap.get(uidl).get("Subject") + ".eml";
            a.href = URL.createObjectURL(blob);
            a.dataset.downloadurl = ["message/rfc822", a.download, a.href].join(':');
            a.style.display = "none";
            document.body.appendChild(a);
            a.click();
            document.body.removeChild(a);
            setTimeout(function() { URL.revokeObjectURL(a.href); }, 1500);
        }
    });
}


function exit_application(){
    var request = new Empty();
    mailService.exitApplication(request, {}, (err, response) => {});
    sessionStorage.setItem("app-closed", "_")
    window.onbeforeunload = function () {};
    $("#main-body").html("<h1>Successfully closed application. You can now safely close this window.</h1>");
}


$(function(){ // run when DOM finished rendering
    if (sessionStorage.getItem("app-closed") === null){
        window.onbeforeunload = function () {return false;}
        if (sessionStorage.getItem("current-page") === null) {
            sessionStorage.setItem("current-page", "1");
        }
        refresh_view();
    } else {
        $("#main-body").html("<h1>Successfully closed application. You can now safely close this window.</h1>");
    }
});


module.exports={
    mark_mail_deleted: mark_mail_deleted,
    reset_trash: reset_trash,
    next_page: next_page,
    prev_page: prev_page,
    download_mail: download_mail,
    reset_trash: reset_trash,
    update_mailbox: update_mailbox,
    exit_application: exit_application
}

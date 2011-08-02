   1. $('.delete_post').bind('ajax:success', function() {  
   2.     $(this).closest('tr').fadeOut();  
   3. });  

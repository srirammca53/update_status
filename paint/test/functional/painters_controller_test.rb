require 'test_helper'

class PaintersControllerTest < ActionController::TestCase
  setup do
    @painter = painters(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:painters)
  end

  test "should get new" do
    get :new
    assert_response :success
  end

  test "should create painter" do
    assert_difference('Painter.count') do
      post :create, :painter => @painter.attributes
    end

    assert_redirected_to painter_path(assigns(:painter))
  end

  test "should show painter" do
    get :show, :id => @painter.to_param
    assert_response :success
  end

  test "should get edit" do
    get :edit, :id => @painter.to_param
    assert_response :success
  end

  test "should update painter" do
    put :update, :id => @painter.to_param, :painter => @painter.attributes
    assert_redirected_to painter_path(assigns(:painter))
  end

  test "should destroy painter" do
    assert_difference('Painter.count', -1) do
      delete :destroy, :id => @painter.to_param
    end

    assert_redirected_to painters_path
  end
end
